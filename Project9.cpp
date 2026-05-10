#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

class Product {
private:
    string name;
    int price;
    int quantity;

public:
    Product(string n, int p, int q) {
        name = n;
        price = p;
        quantity = q;
    }

    int getTotalPrice() const {
        return price * quantity;
    }

    void printInfo() const {
        cout << "- " << name << "[" << quantity << "개] : "
            << getTotalPrice() << "원"
            << " (단가: " << price << "원)" << endl;
    }
};

class ShoppingCart {
private:
    vector<Product*> cart;
    vector<Product*> orderHistory;

public:
    ~ShoppingCart() {
        clearCart();

        for (int i = 0; i < orderHistory.size(); i++) {
            delete orderHistory.at(i);
        }

        orderHistory.clear();
    }

    void addProduct() {
        string name;
        int price;
        int quantity;

        cout << endl;
        cout << "[장바구니 담기]" << endl;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "상품 이름 : ";
        getline(cin, name);

        cout << "가격 : ";
        cin >> price;

        cout << "수량 : ";
        cin >> quantity;

        Product* product = new Product(name, price, quantity);
        cart.push_back(product);

        cout << "상품 추가 완료했습니다." << endl;
    }

    void showCart() const {
        cout << endl;
        cout << "-------- [장바구니 목록] --------" << endl;

        if (cart.empty()) {
            cout << "(장바구니에 담긴 상품이 없습니다.)" << endl;
        }
        else {
            for (int i = 0; i < cart.size(); i++) {
                cart.at(i)->printInfo();
            }
        }

        cout << "--------------------------------" << endl;
    }

    void checkout() {
        cout << endl;
        cout << "-------- [결제 상세 내역] --------" << endl;

        if (cart.empty()) {
            cout << "장바구니에 담긴 상품이 없습니다." << endl;
            return;
        }

        int total = 0;

        for (int i = 0; i < cart.size(); i++) {
            cart.at(i)->printInfo();
            total += cart.at(i)->getTotalPrice();
        }

        cout << "--------------------------------" << endl;
        cout << "최종 결제 금액 : " << total << "원" << endl;

        char answer;

        cout << "결제하시겠습니까? (Y/N) : ";
        cin >> answer;

        if (answer == 'Y' || answer == 'y') {
            orderHistory.insert(orderHistory.end(), cart.begin(), cart.end());
            cart.clear();

            cout << "결제가 완료되었습니다. 장바구니를 비웁니다." << endl;
        }
        else if (answer == 'N' || answer == 'n') {
            cout << "결제가 취소되었습니다." << endl;
        }
        else {
            cout << "잘못된 입력입니다. 결제를 취소합니다." << endl;
        }
    }

    void showOrderHistory() const {
        cout << endl;
        cout << "[주문 상세 내역]" << endl;

        if (orderHistory.empty()) {
            cout << "(결제 내역이 없습니다.)" << endl;
        }
        else {
            for (int i = 0; i < orderHistory.size(); i++) {
                orderHistory.at(i)->printInfo();
            }
        }
    }

    void clearCart() {
        for (int i = 0; i < cart.size(); i++) {
            delete cart.at(i);
        }

        cart.clear();
    }
};

int main() {
    ShoppingCart shop;
    int menu;

    while (true) {
        cout << endl;
        cout << "======== 쇼핑몰 장바구니 시스템 ========" << endl;
        cout << "1. 장바구니 담기" << endl;
        cout << "2. 장바구니 목록 보기" << endl;
        cout << "3. 결제하기" << endl;
        cout << "4. 전체 결제 내역 확인" << endl;
        cout << "5. 프로그램 종료" << endl;
        cout << ">> 메뉴 선택 : ";

        cin >> menu;

        if (menu == 1) {
            shop.addProduct();
        }
        else if (menu == 2) {
            shop.showCart();
        }
        else if (menu == 3) {
            shop.checkout();
        }
        else if (menu == 4) {
            shop.showOrderHistory();
        }
        else if (menu == 5) {
            cout << endl;
            cout << "프로그램을 종료합니다." << endl;
            break;
        }
        else {
            cout << "잘못된 번호입니다. 1~5 사이만 입력해주세요." << endl;
        }
    }

    return 0;
}