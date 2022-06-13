#include <bits/stdc++.h>  
using namespace std;


class Item{
public:
	string name;
	float price;
	string isImported;
	int category; //   0 - book, 1- medicine, 2-food, 3-other
	Item(string name,float price, string isImported,int category){
		this->name=name;
		this->price=price;
		this->isImported=isImported;
		this->category=category;
	}
};


class ShoppingMall{
private:
	vector<pair<Item,int>> shopItem;
	unordered_map<string,int>itemsMap;
public:

	void addItem(Item item,int qty){
		if(itemsMap.find(item.name)!=itemsMap.end()){
			shopItem[itemsMap[item.name]].second+=qty;
		}
		else{
			shopItem.push_back({item,qty});
			itemsMap[item.name]=shopItem.size()-1;
		}
	}

	Item getItem(int no){
		return shopItem[no].first;
	}
	int getQuantity(int no){
		return shopItem[no].second;
	}
	void updateItem(vector<pair<int,int>>shopList){
		for(auto list:shopList){
			shopItem[list.first].second-=list.second;
		}
	}
	void printItem(){
		cout << setw(10) << "ItemNo" <<setw(40) << "Item Name" <<setw(10) << "quantity" << '\n';
		for(int i=0;i<shopItem.size();i++){
			if(shopItem[i].second)
				cout<<setw(10)<<i<<setw(40)<<shopItem[i].first.name<<setw(10)<<shopItem[i].second <<endl;
		}
	}
};

class ShoppingCart{
public:
	vector<pair<Item,int>>shopCart;
	float totalTax;
	float totalPrice;
	ShoppingCart(){
		totalTax=0;
		totalTax=0;
	}
	void addToCart(Item item,int qty){
		shopCart.push_back({item,qty});
	}
	void checkOut(){
		for(auto item:shopCart){
			cout<<item.second<<" "<<item.first.name<<" ";
			float tax=calculateTax(item.first,item.second);
			cout<< item.first.price+tax<<endl;;
			totalTax+=tax;
			totalPrice+=item.first.price+tax;
		}
		cout<<"Tax "<<totalTax<<endl;
		cout<<"Price "<<totalPrice<<endl;
		shopCart.clear();

	}
	float calculateTax(Item item, int qty)
	{
		float tax=0;
		if(item.isImported=="yes")
			tax+=(item.price*qty*5)/100;
		if(item.category==3)
			tax+=(item.price*qty*10)/100;
		return ceil(tax*20)/20;
	}
};

int main()  
{  
	ShoppingMall mall;
	string name;
	int qty;
	float price;
	string isImported;
	int category;

	fstream file;
	string word, t, q, filename;
	filename = "items.txt";
	file.open(filename.c_str());
	while (file >> word)
	{
		name=word;
		file>>word;
		qty=stoi(word);
		file>>word;
		price=stof(word);
		file>>word;
		category=stoi(word);
		cout<<word<<endl;
		file>>word;
		isImported=word;
		Item item(name,price,isImported,category);
		mall.addItem(item,qty);
	}
	

	bool isShopping=true;
	while(isShopping){
		vector<pair<int,int>> shopList;
		char ans;
		ShoppingCart cart;
		bool isCheckout=false;

		cout<<"\n\n ----------List of Items available for shopping---------------\n";
		mall.printItem();
		cout<<"\n ------------------------------------------------------------------\n";


		cout<<"Please select the Item no from above list to add to cart\n";


		int n;
		while(!isCheckout){
			cout<<"Enter the No ";
			cin>>n;
			Item item=mall.getItem(n);
			cout<<"Enter the quantity ";
			do{
				cin>> qty;
				if(qty>0 &&qty>mall.getQuantity(n)){
					cout<<"Please enter the quantity lesser than available ";
				}
			}while(qty>0 &&qty>mall.getQuantity(n));
			cart.addToCart(item,qty);
			shopList.push_back({n,qty});
			cout<<"if you want to add more item to cart press y else n to checkOut\n";
			cin>>ans;
			if(ans=='Y'|| ans =='y')
				continue;
			else
				isCheckout=true;
		}
		cart.checkOut();  // checkout the items in cart
		mall.updateItem(shopList); // update the items quantity after checkout
		cout<<"if you want to shop again press y else n to close\n";
		cin>>ans;
		if(ans=='Y'|| ans =='y')
			continue;
		else
			isShopping=false;
	}
}  
