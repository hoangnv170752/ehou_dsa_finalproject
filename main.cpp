#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

struct Book
{
    string name;
    int price;
    int type;
};

struct Node
{
    Book info;
    Node *next;
};

struct LIST
{
    Node *head;
    Node *tail;
};

struct Invoice
{
    string customerName;
    int totalAmount;
    int quantity;
};

struct DNode
{
    Invoice info;
    DNode *next;
    DNode *prev;
};

struct DLIST
{
    DNode *head;
    DNode *tail;
};

/**
 * @brief Add Book
 *
 */
// Thêm sách 
void addBook(LIST &lst, Book book)
{
    Node *p = new Node;
    p->info = book;
    p->next = NULL;
    if (lst.head == NULL)
    {
        lst.head = lst.tail = p;
    }
    else
    {
        lst.tail->next = p;
        lst.tail = p;
    }
}
void addBook(LIST lst)
{
    Book book;
    cout << "Nhập vào thông tin sách :" << endl;
    cout << "Tên sách: ";
    cin >> book.name;
    cout << "Loại sách (nhập số): ";
    cin >> book.type;
    cout << "Giá sách (nhập số): ";
    cin >> book.price;
    addBook(lst, book);
}
/**
 * @brief Update Book
 *
 * @param lst
 * @param name
 * @param newBook
 * @return true
 * @return false
 */
// Cập nhật sách 
bool updateBook(LIST &lst)
{
    Book newBook;
    string name;
    cout << "Nhập tên sách:" << endl;
    cin >> name;
    cout << "Nhập lại thông tin sách :" << endl;
    cout << "Tên sách: ";
    cin >> newBook.name;
    cout << "Loại sách (nhập số): ";
    cin >> newBook.type;
    cout << "Giá sách (nhập số): ";
    cin >> newBook.price;
    Node *p = lst.head;
    while (p != NULL)
    {
        if (p->info.name == name)
        {
            p->info = newBook;
            return true;
        }
        p = p->next;
    }
    return false;
}
/**
 * @brief Remove Book
 *
 * @param lst
 * @param name
 * @return true
 * @return false
 */
// Xoá sách
bool removeBook(LIST &lst)
{
    string name;
    cout << "Nhập tên sách cần xóa:" << endl;
    cin >> name;
    if (lst.head == NULL)
    {
        cout << "Không có cuốn này:" << endl;
        return false;
    }

    if (lst.head->info.name == name)
    {
        Node *p = lst.head;
        lst.head = lst.head->next;
        delete p;
        cout << "Xóa sách thành công" << endl;
        return true;
    }

    Node *p = lst.head->next;
    Node *prev = lst.head;
    while (p != NULL)
    {
        if (p->info.name == name)
        {
            prev->next = p->next;
            if (p == lst.tail)
            {
                lst.tail = prev;
            }
            delete p;
            cout << "Xóa sách thành công" << endl;
            return true;
        }
        prev = p;
        p = p->next;
    }
    cout << "Xóa sách thất bại" << endl;
    return false;
}
/**
 * @brief Search By Name
 *
 * @param list
 * @param name
 */
// Tìm kiếm sách theo tên 
void searchByName(LIST &list)
{
    string name;
    cout << "Tìm kiếm theo tên: ";
    cin >> name;

    Node *p = list.head;
    bool found = false;
    while (p != NULL)
    {
        if (p->info.name == name)
        {
            cout << "Kết quả tìm được: " << p->info.name << ", " << p->info.type << ", " << p->info.price << endl;
            found = true;
        }
        p = p->next;
    }
    if (!found)
    {
        cout << "Không tìm thấy." << endl;
    }
}
/**
 * @brief Search By Price
 *
 * @param list
 * @param price
 */
// Tìm kiếm theo giá của sách
void searchByPrice(LIST &list)
{
    int price;
    cout << "Tìm kiếm theo giá: ";
    cin >> price;

    Node *p = list.head;
    bool found = false;
    while (p != NULL)
    {
        if (p->info.price == price)
        {
            cout << "Tìm được: " << p->info.name << ", " << p->info.type << ", " << p->info.price << endl;
            found = true;
        }
        p = p->next;
    }
    if (!found)
    {
        cout << "Không tìm thấy." << endl;
    }
}
/**
 * @brief Sort By Name of Book
 *
 * @param lst
 */
// Tìm sách theo tên cuốn sách 
void sortBookByName(LIST &lst)
{
    Node *i, *j, *prev_j;
    Book key;
    if (lst.head == nullptr || lst.head->next == nullptr)
    {
        return;
    }

    i = lst.head->next;
    while (i != nullptr)
    {
        key = i->info;
        j = lst.head;
        prev_j = nullptr;

        while (j != i && key.name > j->info.name)
        {
            prev_j = j;
            j = j->next;
        }

        if (j != i)
        {
            i->next = j;
            if (prev_j != nullptr)
            {
                prev_j->next = i;
            }
            else
            {
                lst.head = i;
            }
        }
        i = i->next;
    }
    Node *p = lst.head;
    while (p->next != nullptr)
    {
        p = p->next;
    }
    lst.tail = p;
}

/**
 * @brief Sort By Price of Book
 *
 * @param lst
 */
// Tìm sách theo giá sách 
void sortBookByPrice(LIST &lst)
{
    Node *i, *j, *prev_j;
    Book key;

    if (lst.head == nullptr || lst.head->next == nullptr)
    {
        return;
    }

    i = lst.head->next;
    while (i != nullptr)
    {
        key = i->info;
        j = lst.head;
        prev_j = nullptr;
        while (j != i && key.price > j->info.price)
        {
            prev_j = j;
            j = j->next;
        }

        if (j != i)
        {
            i->next = j;
            if (prev_j != nullptr)
            {
                prev_j->next = i;
            }
            else
            {
                lst.head = i;
            }
        }
        i = i->next;
    }

    Node *p = lst.head;
    while (p->next != nullptr)
    {
        p = p->next;
    }
    lst.tail = p;
}

/**
 * @brief Sort List By Name of Book
 *
 * @param list
 */
// Lọc danh sách theo tên của sách 
void sortListByName(DLIST &list)
{
    if (list.head == nullptr || list.head == list.tail)
    {
        return;
    }

    DNode *curr = list.head->next;

    while (curr != nullptr)
    {
        DNode *temp = curr;
        string name = curr->info.customerName;
        while (temp->prev != nullptr && temp->prev->info.customerName > name)
        {
            temp = temp->prev;
        }
        if (temp->prev == nullptr && temp->info.customerName > name)
        {
            curr->prev->next = curr->next;
            if (curr->next != nullptr)
            {
                curr->next->prev = curr->prev;
            }
            else
            {
                list.tail = curr->prev;
            }
            curr->prev = nullptr;
            curr->next = temp;
            temp->prev = curr;
            list.head = curr;
        }
        else if (temp != curr)
        {
            curr->prev->next = curr->next;
            if (curr->next != nullptr)
            {
                curr->next->prev = curr->prev;
            }
            else
            {
                list.tail = curr->prev;
            }
            curr->prev = temp->prev;
            curr->next = temp;
            temp->prev->next = curr;
            temp->prev = curr;
        }
        curr = curr->next;
    }
}
/**
 * @brief Sort List By Total Amount
 *
 * @param list
 */
// Lọc danh sách theo tổng số 
void sortListByTotalAmount(DLIST &list)
{
    if (list.head == nullptr || list.head == list.tail)
    {
        return;
    }
    DNode *curr = list.head->next;
    while (curr != nullptr)
    {
        Invoice tmp = curr->info;
        DNode *prev = curr->prev;
        while (prev != nullptr && prev->info.totalAmount > tmp.totalAmount)
        {
            prev->next->info = prev->info;
            prev = prev->prev;
        }
        if (prev == nullptr)
        {
            list.head->info = tmp;
        }
        else
        {
            prev->next->info = tmp;
        }
        curr = curr->next;
    }
}
void displayBook(Book p)
{
    cout << "Tên sách: " << p.name << ", Loại sách: " << p.type << ", Giá: " << p.price << endl;
}
/**
 * @brief Find Max by Price
 *
 * @param list
 * @return Books
 */
// Tìm phần tử lớn nhất trong danh sách liên kết đơn
void findMaxByPrice(LIST list)
{
    // Trường hợp danh sách rỗng
    if (list.head == nullptr)
    {
        displayBook(Book{"", 0, 0});
    }
    else
    {
        // Duyệt danh sách liên kết đơn từ đầu đến cuối để tìm phần tử lớn nhất
        Node *curr = list.head;
        Book maxBook = curr->info;
        while (curr != nullptr)
        {
            if (curr->info.price > maxBook.price)
            {
                maxBook = curr->info;
            }
            curr = curr->next;
        }
        displayBook(maxBook);
    }
}

// Tìm phần tử nhỏ nhất trong danh sách liên kết đơn
void findMinByPrice(LIST list)
{
    // Trường hợp danh sách rỗng
    if (list.head == nullptr)
    {
        displayBook(Book{"", 0, 0});
    }
    else
    {
        // Duyệt danh sách liên kết đơn từ đầu đến cuối để tìm phần tử nhỏ nhất
        Node *curr = list.head;
        Book minBook = curr->info;
        while (curr != nullptr)
        {
            if (curr->info.price < minBook.price)
            {
                minBook = curr->info;
            }
            curr = curr->next;
        }
        displayBook(minBook);
    }
}
/**
 * Calculate Sum
 * */
void sum(LIST list)
{
    int sum = 0;
    Node *p = list.head;
    while (p != NULL)
    {
        sum += p->info.price;
        p = p->next;
    }
    cout << "Tổng tiền mặt hàng 'SACH' : " << sum << " VND";
}
/**
 * Calculate average
 * */

void average(LIST list)
{
    if (list.head == NULL)
    {
        cout << "Tổng tiền trung bình mặt hàng 'SACH' : " << 0 << " VND";
    }
    else
    {
        int sum = 0, count = 0;
        Node *p = list.head;
        while (p != NULL)
        {
            sum += p->info.price;
            count++;
            p = p->next;
        }
        cout << "Tổng tiền trung bình mặt hàng 'SACH' : " << (float)sum / count << " VND";
    }
}

// Hàm đếm số lượng sản phẩm trong danh sách
void count(LIST list)
{
    int count = 0;
    Node *p = list.head;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }
    cout << "Số lượng 'SACH' có trong hệ thống : " << count << " chiec";
}

// Hàm tính tổng giá trị của các sản phẩm có kích cỡ nhỏ hơn một giá trị cho trước
void sumByType(LIST list)
{
    int typeLimit;
    cout << "giới hạn của loại sách : ";
    cin >> typeLimit;

    int sum = 0;
    Node *p = list.head;
    while (p != NULL)
    {
        if (p->info.type < typeLimit)
        {
            sum += p->info.price;
        }
        p = p->next;
    }

    cout << "Tổng tiền 'SACH' được sắp xếp nhỏ hơn loại :   " << typeLimit << " = " << sum << " VND";
}

// Hàm tính số lượng sản phẩm có giá trị lớn hơn một giá trị cho trước
void countByPrice(LIST list)
{
    int priceLimit;
    cout << "Giới hạn số lượng theo giá trị của sách : ";
    cin >> priceLimit;

    int count = 0;
    Node *p = list.head;
    while (p != NULL)
    {
        if (p->info.price > priceLimit)
        {
            count++;
        }
        p = p->next;
    }
    cout << "Số lượng 'SACH' có giá lớn hơn  " << priceLimit << " = " << count << " chiec.";
}
//Đưa ra danh sách các sách
void displayBook(LIST lst)
{
    cout << "Danh sách của sách: " << endl;
    Node *p = lst.head;
    while (p != NULL)
    {
        cout << "Tên: " << p->info.name << ", Loại sách (số): " << p->info.type << ", Giá sách (số): " << p->info.price << endl;
        p = p->next;
    }
}
//Đưa ra đầu vào của sách 
void inputBookList(LIST &lst)
{
    int n;
    cout << "Nhập vào số lượng sách: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        Book book;
        cout << "Nhập vào cuốn sách thứ #" << i + 1 << ":" << endl;
        cout << "Tên: ";
        cin >> book.name;
        cout << "Loại sách (nhập số): ";
        cin >> book.type;
        cout << "Giá tiền của sách: ";
        cin >> book.price;
        addBook(lst, book);
    }
}
// Nhập thông tin khách hàng
void addInvoice(DLIST &dlst, Invoice inv)
{
    DNode *p = new DNode;
    p->info = inv;
    p->next = NULL;
    p->prev = dlst.tail;
    if (dlst.head == NULL)
    {
        dlst.head = dlst.tail = p;
    }
    else
    {
        dlst.tail->next = p;
        dlst.tail = p;
    }
}

void addInvoice(DLIST &dlst)
{
    Invoice inv;
    cout << "Nhập hóa đơn " << endl;
    cout << "Tên khách hàng: ";
    cin >> inv.customerName;
    cout << "Số lượng: ";
    cin >> inv.quantity;
    cout << "Tổng đơn hàng: ";
    cin >> inv.totalAmount;
    addInvoice(dlst, inv);
}
//Đưa ra thông tin khách hàng 
void displayInvoice(Invoice p)
{
    cout << "Tên khách hàng: " << p.customerName << ", Tổng đơn hàng: " << p.totalAmount << ", Số lượng: "
         << p.totalAmount << endl;
}
// Cập nhật thông tin khách hàng 
bool updateInvoice(DLIST &lst)
{
    string customerName;
    Invoice newIn;

    cout << "Tên khách hàng muốn cập nhật: ";
    cin >> newIn.customerName;

    cout << "Nhập vào hóa đơn " << endl;
    cout << "Tên khách hàng: ";
    cin >> newIn.customerName;
    cout << "Số lượng: ";
    cin >> newIn.quantity;
    cout << "Tổng đơn hàng: ";
    cin >> newIn.totalAmount;

    DNode *p = lst.head;
    while (p != NULL)
    {
        if (p->info.customerName == customerName)
        {
            p->info = newIn;
            return true;
        }
        p = p->next;
    }
    return false;
}
//Xoá thông tin khách hàng 
bool removeInvoice(DLIST &lst)
{
    string customerName;
    cout << "Tên khách hàng muốn xóa: ";
    cin >> customerName;

    DNode *p = lst.head;
    while (p != NULL)
    {
        if (p->info.customerName == customerName)
        {
            if (p == lst.head && p == lst.tail)
            {
                lst.head = lst.tail = NULL;
            }
            else if (p == lst.head)
            {
                lst.head = p->next;
                lst.head->prev = NULL;
            }
            else if (p == lst.tail)
            {
                lst.tail = p->prev;
                lst.tail->next = NULL;
            }
            else
            {
                p->prev->next = p->next;
                p->next->prev = p->prev;
            }
            delete p;
            return true;
        }
        p = p->next;
    }
    return false;
}
//Tìm kiếm thông tin khách hàng 
void *searchInvoiceByName(DLIST DQ)
{
    string customerName;
    cout << "Tìm kiếm theo tên khách hàng: ";
    cin >> customerName;

    DNode *p;
    p = DQ.head;
    while (p != NULL)
    {
        if (p->info.customerName == customerName)
        {
            cout << "Tìm được: " << p->info.customerName << ", " << p->info.quantity << ", " << p->info.totalAmount
                 << endl;
        }
        p = p->next;
    }
}
// Tìm giá trị tổng số lượng lớn nhất 
void findMaxByTotalAmount(DLIST list)
{
    // Trường hợp danh sách rỗng
    if (list.head == nullptr)
    {
        displayInvoice(Invoice{"", 0, 0});
    }
    else
    {
        DNode *curr = list.head;
        Invoice maxInvoice = curr->info;
        while (curr != nullptr)
        {
            if (curr->info.totalAmount > maxInvoice.totalAmount)
            {
                maxInvoice = curr->info;
            }
            curr = curr->next;
        }
        displayInvoice(maxInvoice);
    }
}
// Tìm giá trị tổng số lượng nhỏ nhất 
Invoice findMinTotalAmount(DLIST list)
{
    if (list.head == nullptr)
    {
        displayInvoice(Invoice{"", 0, 0});
    }
    else
    {
        DNode *curr = list.head;
        Invoice minInvoice = curr->info;
        while (curr != nullptr)
        {
            if (curr->info.totalAmount < minInvoice.totalAmount)
            {
                minInvoice = curr->info;
            }
            curr = curr->next;
        }
        displayInvoice(minInvoice);
    }
}
//Tính tổng 
void getTotal(DLIST list)
{
    if (list.head == nullptr)
    {
        cout << "Tổng tiền 'HOA DON' : " << 0 << " VND";
    }
    else
    {
        DNode *curr = list.head;
        int total = 0;
        while (curr != nullptr)
        {
            total += curr->info.totalAmount;
            curr = curr->next;
        }
        cout << "Tổng tiền 'HOA DON' : " << total << " VND";
    }
}
//Tính trung bình 
void getAverage(DLIST list)
{
    // Trường hợp danh sách rỗng
    if (list.head == nullptr)
    {
        cout << "Tổng tiền trung bình 'HOA DON'" << 0 << " VND";
    }
    else
    {
        // Tính tổng và đếm số lượng phần tử trong danh sách liên kết kép
        int total = 0;
        int count = 0;
        DNode *curr = list.head;
        while (curr != nullptr)
        {
            total += curr->info.totalAmount;
            count++;
            curr = curr->next;
        }

        cout << "Tổng tiền trung bình 'HOA DON'" << (float)total / count << " VND";
    }
}
// Đếm số lượng 
int getCount(DLIST list)
{
    if (list.head == nullptr)
    {
        cout << "Số lượng 'HOA DON' : " << 0;
        return 0;
    }
    else
    {
        int count = 0;
        DNode *curr = list.head;
        while (curr != nullptr)
        {
            count++;
            curr = curr->next;
        }
        cout << "Số lượng 'HOA DON' : " << count;
    }
}
// Tìm các hoá đơn có giá trị hơn 50000
void findLargeInvoices(DLIST list)
{
    DNode *p = list.head;
    bool found = false;
    cout << "Các hóa đơn có giá trị hơn 50000:" << endl;
    while (p != NULL)
    {
        if (p->info.totalAmount > 50000)
        {
            found = true;
            cout << "Hóa đơn của khách hàng " << p->info.customerName << " có giá trị " << p->info.totalAmount << endl;
        }
        p = p->next;
    }
    if (!found)
    {
        cout << "Không có hóa đơn nào giá trị hơn 50000." << endl;
    }
}
//Đếm số lượng sản phẩm bởi khách hàng 
void countProductByCustomerName(DLIST list)
{
    string customerName;
    cout << "Nhập số tiền của khách hàng \n";
    cin >> customerName;

    int count = 0;
    DNode *p = list.head;
    while (p != NULL)
    {
        if (p->info.customerName == customerName)
        {
            count += p->info.quantity;
        }
        p = p->next;
    }
    cout << "Khách hàng " << customerName << "đã mua " << count << " sản phẩm.";
}
// Đưa ra hoá đơn 
void displayInvoice(DLIST dlst)
{
    cout << "Danh sách các hóa đơn: " << endl;
    DNode *p = dlst.head;
    while (p != NULL)
    {
        cout << "Tên khách hàng: " << p->info.customerName << ", Tổng hóa đơn: " << p->info.totalAmount << ", Số lượng: "
             << p->info.totalAmount << endl;
        p = p->next;
    }
}
//Nhập vào thông tin khách hàng
void inputInvoiceList(DLIST &lst)
{
    int n;
    cout << "Nhập vào số lượng các hóa đơn: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        Invoice inv;
        cout << "Nhập hóa đơn thứ #" << i + 1 << ":" << endl;
        cout << "Tên khách hàng: ";
        cin >> inv.customerName;
        cout << "Số lượng : ";
        cin >> inv.quantity;
        cout << "Tổng hóa đơn: ";
        cin >> inv.totalAmount;
        addInvoice(lst, inv);
    }
}
//Lưu file hoá đơn ra máy 
void saveCustomerToFile(DLIST& InvoiceList) {
    string filePath;
    cout << "Nhập vào đường dẫn file để lưu thông tin người dùng: ";
    cin >> filePath;
    ofstream outputFile;
    outputFile.open(filePath);
    if (!outputFile) {
        cerr << "Lỗi không tạo được file " << filePath << endl;
        return;
    }
    DNode* current = InvoiceList.head;
    while (current != NULL) {
        outputFile << "Tên khách hàng: " << current->info.customerName << endl;
        outputFile << "Số lượng: " << current->info.quantity << endl;
        outputFile << "Tổng số hoá đơn : " << current->info.totalAmount << endl;
        outputFile << endl;
        current = current->next;
    }
    outputFile.close();
    cout << "Dữ liệu khách hàng đã được lưu vào file : " << filePath << endl;
}
// Chương trình chính 
int main()
{
    LIST bookList;
    DLIST invoiceList;
    bookList.head = NULL;
    bookList.tail = NULL;
    invoiceList.head = NULL;
    invoiceList.tail = NULL;

    int choice, choice1, choice2, choice3, choice4, choice5, choice6, choice7;
    do
    {
        cout << "| ********************* | \n";
        cout << "Menu:\n";
        cout << "1. Nhap-In danh sach 'Sach' - 'Hoa don khach hang' .\n";
        cout << "2. Thêm -  sửa - xóa hàng hóa.\n";
        cout << "3. Tìm kiếm.\n";
        cout << "4. Sắp xếp mặt hàng \n";
        cout << "5. Tìm kiếm phần tử lớn nhất, nhỏ nhất. \n";
        cout << "6. Tính tổng, trung bình và đếm mặt hàng . \n";
        cout << "7.Thống kê. \n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon cua ban: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            do
            {
                cout << "| ********************* | \n";
                cout << "MENU CHUC NANG 1:\n";
                cout << "1.1 Nhap danh sach 'SACH'\n";
                cout << "1.2 Nhap danh sach 'HOA DON'\n";
                cout << "1.3 Hien thi danh sach 'SACH'\n";
                cout << "1.4 Hien thi danh sach 'HOA DON'\n";
                cout << "1.5 Luu file danh sach 'HOA DON'\n";
                cout << "0. Tro ve\n";
                cout << "Nhap lua chon cua ban: ";
                cin >> choice1;
                cout << "\n";
                cout << "| ********************* | \n";
                switch (choice1)
                {
                case 1:
                    inputBookList(bookList);
                    break;
                case 2:
                    inputInvoiceList(invoiceList);
                    break;
                case 3:
                    displayBook(bookList);
                    break;
                case 4:
                    displayInvoice(invoiceList);
                    break;
                case 5:
                    saveCustomerToFile(invoiceList);
                    break;
                case 0:
                    break;
                default:
                    cout << "Lua chon khong hop le. Vui long nhap lai.\n";
                }
            } while (choice1 != 0);
            break;
        case 2:
            // Code cho chuc nang 2
            do
            {
                cout << "| ********************* | \n";
                cout << "MENU CHUC NANG 2:\n";
                cout << "2.1 Them SACH  \n";
                cout << "2.2 Sua SACH theo ten \n";
                cout << "2.3 Xoa 'SACH' theo ten\n";
                cout << "2.4 Them 'HOA DON'\n";
                cout << "2.5 Sua 'HOA DON' theo ten khach hang\n";
                cout << "2.6 Xoa 'HOA DON' theo ten khach hang\n";
                cout << "0. Tro ve\n";
                cout << "Nhap lua chon cua ban: ";
                cin >> choice2;
            switch (choice2)
                {
                case 1:
                    addBook(bookList);
                    break;
                case 2:
                    updateBook(bookList);
                    break;
                case 3:
                    removeBook(bookList);
                    break;
                case 4:
                    addInvoice(invoiceList);
                    break;
                case 5:
                    updateInvoice(invoiceList);
                    break;
                case 6:
                    removeInvoice(invoiceList);
                    break;
                case 0:
                    break;
                default:
                    cout << "Lua chon khong hop le. Vui long nhap lai.\n";
                }
            } while (choice2 != 0);
            break;
        case 3:
            do
            {
                cout << "| ********************* | \n";
                cout << "MENU CHUC NANG 3:\n";
                cout << "3.1 Tim kiem 'SACH' theo ten  \n";
                cout << "3.2 Tim kiem 'HOA DON' theo ten khach hang \n";
                cout << "0. Tro ve\n";
                cout << "Nhap lua chon cua ban: ";
                cin >> choice3;
                switch (choice3)
                {
                case 1:
                    searchByName(bookList);
                    break;
                case 2:
                    searchInvoiceByName(invoiceList);
                    break;
                case 0:
                    break;
                default:
                    cout << "Lua chon khong hop le. Vui long nhap lai.\n";
                }
            } while (choice3 != 0);
            break;
        case 4:
            do
            {
                cout << "| ********************* | \n";
                cout << "MENU CHUC NANG 4:\n";
                cout << "4.1 Sap xem 'SACH' theo ten ten san pham\n";
                cout << "4.2 Sap xem 'SACH' theo gia tien\n";
                cout << "4.3 Sap xep 'HOA DON' theo ten khach hang \n";
                cout << "4.4 Sap xep 'HOA DON' theo tong tien hoa don\n";
                cout << "0. Tro ve\n";
                cout << "Nhap lua chon cua ban: ";
                cin >> choice4;
                switch (choice4)
                {
                case 1:
                    sortBookByName(bookList);
                    break;
                case 2:
                    sortBookByPrice(bookList);
                    break;
                case 3:
                    sortListByName(invoiceList);
                    break;
                case 4:
                    sortListByTotalAmount(invoiceList);
                    break;
                case 0:
                    break;
                default:
                    cout << "Lua chon khong hop le. Vui long nhap lai.\n";
                }
            } while (choice4 != 0);
            break;
        case 5:
            do
            {
                cout << "| ********************* | \n";
                cout << "MENU CHUC NANG 5:\n";
                cout << "5.1 'SACH' co gia cao nhat\n";
                cout << "5.2 'SACH' co gia thap nhat\n";
                cout << "5.3 'HOA DON' co don gia cao nhat \n";
                cout << "5.4 'HOA DON' co don gia cao nhat\n";
                cout << "0. Tro ve\n";
                cout << "Nhap lua chon cua ban: ";
                cin >> choice5;
                switch (choice5)
                {
                case 1:
                    findMaxByPrice(bookList);
                    break;
                case 2:
                    findMinByPrice(bookList);
                    break;
                case 3:
                    findMaxByTotalAmount(invoiceList);
                    break;
                case 4:
                    findMinTotalAmount(invoiceList);
                    break;
                case 0:
                    break;
                default:
                    cout << "Lua chon khong hop le. Vui long nhap lai.\n";
                }
            } while (choice5 != 0);
            break;
        case 6:
            do
            {
                cout << "| ********************* | \n";
                cout << "MENU CHUC NANG 6:\n";
                cout << "6.1 Tong tien mat hang 'SACH'\n";
                cout << "6.2 Tong tien trung binh mat hang 'SACH'\n";
                cout << "6.3 So luong 'SACH' co trong he thong\n";
                cout << "6.4 Tong tien 'HOA DON'\n";
                cout << "6.5 Tong tien trung binh 'HOA DON'\n";
                cout << "6.6 So luong 'HOA DON' \n";
                cout << "0. Tro ve\n";
                cout << "Nhap lua chon cua ban: ";
                cin >> choice6;
                switch (choice6)
                {
                case 1:
                    sum(bookList);
                    break;
                case 2:
                    average(bookList);
                    break;
                case 3:
                    count(bookList);
                    break;
                case 4:
                    getTotal(invoiceList);
                    break;
                case 5:
                    getAverage(invoiceList);
                    break;
                case 6:
                    getCount(invoiceList);
                    break;
                case 0:
                    break;
                default:
                    cout << "Lua chon khong hop le. Vui long nhap lai.\n";
                }
            } while (choice6 != 0);
            break;
        case 7:
            do
            {
                cout << "| ********************* | \n";
                cout << "MENU CHUC NANG 7:\n";
                cout << "7.1 Tong tien mat hang 'SACH' co size nho hon 12\n";
                cout << "7.2 Tong tien mat hang 'SACH' co gia lon hon 10.000 VND\n";
                cout << "7.3 Nhung 'HOA DON' có tong gia lớn hơn 50.000\n";
                cout << "7.4 Thong ke khach hang mua bao nhieu 'HOA DON'\n";
                cout << "0. Tro ve\n";
                cout << "Nhap lua chon cua ban: ";
                cin >> choice7;
                switch (choice7)
                {
                case 1:
                    sumByType(bookList);
                    break;
                case 2:
                    countByPrice(bookList);
                    break;
                case 3:
                    findLargeInvoices(invoiceList);
                    break;
                case 4:
                    countProductByCustomerName(invoiceList);
                    break;
                case 0:
                    break;
                default:
                    cout << "Lua chon khong hop le. Vui long nhap lai.\n";
                }
            } while (choice7 != 0);
            break;
        case 0:
            break;
        default:
            cout << "Lua chon khong hop le. Vui long nhap lai.\n";
        }
    } while (choice != 0);

    return 0;
}