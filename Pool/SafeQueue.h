template <class T>
class SafeQueue
{
public:
	SafeQueue(void): q(), m(),c() {}
	~SafeQueue(void){}

	// Додаємо елемент до черги
	void Add(T t)
	{
		std::lock_guard<std::mutex> lock(m);
		q.push(t);
		c.notify_one();
	}

	// Забираэмо верхній елемент
	// Якщо черга пуста то чекаємо, поки додадуть елемент
	T dequeue(void)
	{
		std::unique_lock<std::mutex> lock(m);
		while (q.empty())
		{
			c.wait(lock);
		}
		T val = q.front();
		q.pop();
		return val;
	}

private:
	std::queue<T> q;
	mutable std::mutex m;
	std::condition_variable c;
};