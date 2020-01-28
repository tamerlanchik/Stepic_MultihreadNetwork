#include <memory>
#include <iostream>

class Item {
public:
	Item(int a) : _a(a){
		std::cout << "Item created!\n";
	}
	Item(const Item& old) {
		_a = old._a;
		std::cout << "Item created via copy constructor!\n";
	}
	Item(Item &&old) {
		_a = old._a;
		old._a = 0;
		std::cout << "Item created via move contructor!\n";
	}

	Item& operator=(const Item a) {
		std::cout << "Item::operator=\n";
		_a = a._a;
		return *this;
	}

	~Item() {
		std::cout << "Delete item~\n";
	}

	void test(int &e) {
		std::cout << "Item::test(int&)\n";
	}
	void test(int &&e) {
		std::cout << "Item::test(int&&)\n";
	}
private:
	int _a;
};

Item t(int y){
	return Item(y);
}

template<typename T>
T& move(T &&item) {
	return static_cast<T&>(item);
}

int main() {
	Item a = Item(321);
	Item b(1);

	std::shared_ptr<Item> ptr(new Item(123));
	std::unique_ptr<Item> ptr2;

	std::cout << static_cast<bool>(ptr) << std::endl;
	std::cout << static_cast<bool>(ptr2) << std::endl;

	ptr2 = std::move(ptr);

	std::cout << static_cast<bool>(ptr) << std::endl;
	std::cout << static_cast<bool>(ptr2) << std::endl;
}