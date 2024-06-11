#include <iostream>
#include <vector>

template <typename T, typename Collection, typename Iterator>
class MyCollection : public Collection
{
public:
	class MyIterator
	{
		friend MyCollection;
	private:
		Iterator current;
		Collection & collection;

		MyIterator(Collection & col, Iterator const i) : collection(col)
		{
			current = i;
		}

	public:

		T & operator*()
		{
			return *current;
		}

		MyIterator & operator++()
		{
			//TODO zaimplementowaæ operator ++
			auto to = current + 1;
			while(to != collection.end())
			{
				if (*(to) == *current)
				{
					current = to;
					return *this;
				}
				to++;
			}
			auto min = collection.end();
			for (auto i = collection.begin(); i != collection.end(); ++i)
				if (*i > * current && (min == collection.end() || *i < *min))//Dlaczego nie dzia³a?   (*i > * current && (*i < *min || min == collection.end()))
					min = i;
				
			this->current = min;
			return *this;
			
		}

		bool operator!=(MyIterator const& i) const
		{
			return current != i.current;
		}
	};

	MyIterator myBegin()
	{
		//TODO zaimplementowaæ metodê myBegin
		Iterator first = this->begin();
		auto from = this->begin();
		while (from != this->end() )
		{
			if (*first > * from)
				first = from;
			
			++from;
		}
		return MyIterator(*this, first);
	}

	MyIterator myEnd()
	{
		return MyIterator(*this, this->end());
	}
};


int main()
{
	MyCollection<int, std::vector<int>, std::vector<int>::iterator> col;
	
	for (int i = 0; i < 100; ++i)
		col.push_back( rand() % 20 );

	std::cout << "Vector (standard iterator):" << std::endl;
	for( auto const i: col)
		std::cout << i << ", ";
	std::cout << std::endl;

	std::cout << "Vector (my iterator):" << std::endl;
	for (auto i = col.myBegin(); i != col.myEnd(); ++i)
		std::cout << *i << ", ";
	std::cout << std::endl;
}

