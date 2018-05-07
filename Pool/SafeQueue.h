template <class T>
class SafeQueue
{
public:
	SafeQueue(void): q(), m(),c() {}
	~SafeQueue(void){}

	// ������ ������� �� �����
	void Add(T t)
	{
		std::lock_guard<std::mutex> lock(m);
		q.push(t);
		c.notify_one();
	}

	// �������� ������ �������
	// ���� ����� ����� �� ������, ���� �������� �������
	T dequeue(void)
	{
		std::unique_lock<std::mutex> lock(m);
		c.wait_for(lock, timeout, [this] { return !q.empty(); }))
		T val = q.front();
		q.pop();
		return val;
	}

private:
	std::queue<T> q;
	mutable std::mutex m;
	std::condition_variable c;
};