#include <iostream>
#include <list>
#include <algorithm>
#include <utility>

using namespace std;

struct Item
{
	string name;
	int price;
	int weight;
	string description;

	bool operator()(const Item& other)
	{
		return this->name < other.name;
	}
};

class Shop
{
private:
	list<Item> itemList;

public:
	enum class OrderType { Name, Price, Weight };
	class SortOrder
	{
	public:
		OrderType curType;
		bool less;

		bool operator()(const Item& left, const Item& right)
		{
			if (less)
			{
				if (curType == OrderType::Name)
					return left.name < right.name;
				else if (curType == OrderType::Price)
					return left.price < right.price;
				else if (curType == OrderType::Weight)
					return left.weight < right.weight;
			}
			else
			{
				if (curType == OrderType::Name)
					return left.name > right.name;
				else if (curType == OrderType::Price)
					return left.price > right.price;
				else if (curType == OrderType::Weight)
					return left.weight > right.weight;
			}
		}
	};
	SortOrder order;
	
	void Sort(OrderType type, bool less = true)
	{
		order.curType = type;
		order.less = less;
		itemList.sort(order);
	}

	void ShowItems()
	{
		for (list<Item>::iterator iter = itemList.begin();
			iter != itemList.end(); iter++)
		{
			cout << iter->name << '\t';
			cout << "$" << iter->price << '\t';
			cout << iter->weight << "kg" << endl;
		}
		cout << endl << endl;
	}

	void AddItem(string name, int price, int weight)
	{
		Item item;
		item.name = name;
		item.price = price;
		item.weight = weight;
		itemList.push_back(item);
	}
};

int main()
{
	Shop shop;
	shop.AddItem("칼", 100, 200);
	shop.AddItem("방패", 10, 600);
	shop.AddItem("갑옷", 1000, 500);
	shop.AddItem("망토", 200, 10);
	shop.AddItem("망토2", 300, 20);

	shop.ShowItems();

	shop.Sort(Shop::OrderType::Name);
	shop.ShowItems();

	shop.Sort(Shop::OrderType::Price);
	shop.ShowItems();

	shop.Sort(Shop::OrderType::Weight);
	shop.ShowItems();

	shop.Sort(Shop::OrderType::Weight, false);
	shop.ShowItems();
}