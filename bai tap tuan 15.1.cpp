#include<iostream>
using namespace std;
struct node{
	string name;
	int pages;
	node* next; // trỏ đến mục lục cấp ngang hàng
	node* child; // trỏ đến mục lục cấp con
	node(string name, int pages){
		this->name = name;
		this->pages = pages;
		next = NULL;
		child = NULL;
	}
};
void addchild(node* book, string name, int pages){
	node* newnode = new node(name, pages);
	if(book->child == NULL) book->child = newnode;
	else{
		while(book->child != NULL){
			book = book->child;
		}
		book->child = newnode;
	}
}
void addnext(node* node1, string name, int pages){
	node* newnode = new node(name, pages);
	if(node1->next == NULL) node1->next = newnode;
	else{
		while(node1->next != NULL){
			node1 = node1->next;
		}
		node1->next = newnode;
	}
}
//xác định số chương của cuốn sách
int sochuong(node* book){
	int sochuong = 0;
	if(book->child == NULL || book == NULL) return 0;
	else{
		node* temp = book->child;
		sochuong++;
	    while(temp->next != NULL){
		    sochuong++;
		    temp = temp->next;
	    }
	    return sochuong;
	}
}
//Tìm độ dài của mỗi chương
int dodaichuong(node* book){
	if(book == NULL) return 0;
	int pages = book->pages;
	pages += dodaichuong(book->child);
	pages += dodaichuong(book->next);
	return pages;
}
//Tìm chương dài nhất của cuốn sách
void chuong_dai_nhat(node* book) {
    if (book == NULL || book->child == NULL) {
        cout << "Khong ton tai chuong!" << endl;
        return;
    }
    node* temp = book->child;
    node* temp1 = book->child;
    int max = dodaichuong(temp);
    string maxchuong = temp->name;
    while (temp != NULL) {
        if (max <= dodaichuong(temp)) {
            max = dodaichuong(temp);
            maxchuong = temp->name;
        }
        temp = temp->next;
    }
    while (temp1 != NULL) {
        if (maxchuong == temp1->name) {
            cout << maxchuong << " la chuong dai nhat cuon sach!" << endl;
            return;
        }
        temp1 = temp1->next;
    }
}
//Tìm và xóa 1 mục khỏi cuốn sách
//Cập nhật số trang của cuốn sách sau khi xóa
int dodaicuonsach(node* book){
	if(book == NULL){
		return 0;
	}
	int pages = book->pages;
	pages += dodaicuonsach(book->child);
	pages += dodaicuonsach(book->next);
	return pages;
}
void deletenode(node* parent, node* nodeTodelete) {
    if (!parent || !nodeTodelete) return;

    // Nếu nodeTodelete là phần tử tiếp theo của parent
    if (parent->next == nodeTodelete) {
        parent->next = nodeTodelete->next; // Cập nhật liên kết ngang

        // Nếu parent chưa có child, gán child của nodeTodelete vào parent
        if (!parent->child) {
            parent->child = nodeTodelete->child;
        } else {
            // Gắn child của nodeTodelete vào cuối danh sách child của parent
            node* temp = parent->child;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = nodeTodelete->child;
        }
    }
    // Nếu nodeTodelete là child trực tiếp của parent
    else if (parent->child == nodeTodelete) {
        parent->child = nodeTodelete->next; // Cập nhật liên kết ngang cho child

        // Gắn child của nodeTodelete vào danh sách child tiếp theo
        if (nodeTodelete->child) {
            node* temp = nodeTodelete->child;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = parent->child;
            parent->child = nodeTodelete->child;
        }
    }
    // Xóa node
    delete nodeTodelete;
}

void timvaxoa(node* parent, node* book, string name){
	if(!book) return;
	if(book->name == name){
        deletenode(parent, book);
        return;
    }
	timvaxoa(book, book->child, name);
	timvaxoa(book, book->next, name);
}
int main(){
	node* book = new node("Book", 50);
	book->child = new node("Chapter1", 20);
	book->child->next = new node("Chapter2", 25);
	book->child->next->next = new node("Chapter3", 30);
	node* chapter1 = book->child;
	chapter1->child = new node("section11", 5);
	chapter1->child->next = new node("section12", 10);
	chapter1->child->next->next = new node("section13", 15);
	node* chapter2 = book->child->next;
	chapter2->child = new node("section21", 7);
	chapter2->child->next = new node("section22", 12);
	node* chapter3 = book->child->next->next;
	chapter3->child = new node("section31", 9);
	cout<<"So chuong cua cuon sach la "<<sochuong(book)<<endl;
	chuong_dai_nhat(book);
	string name;
	int pages = dodaicuonsach(book);
	cout<<"Ban muon xoa muc :"<<endl;
	cin>>name;
	timvaxoa(book, book, name);
	if(dodaicuonsach(book) < pages) cout<<"Xoa thanh cong! Do dai hien tai cua cuon sach la: "<<dodaicuonsach(book)<<endl;
	else cout<<"Khong tim thay muc can xoa!"<<endl;
	return 0;
}