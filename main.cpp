#include <iostream>
#include <string>
#include <cstring>

using namespace std;

struct Book
{
    string name;
    int price;
    int type;
    int quantity;
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

struct Customer
{
    string customerName;
    int bill;
    int quantity;
};

struct DNode
{
    Customer info;
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
/**
 * @brief Update Book
 *
 * @param lst
 * @param name
 * @param newBook
 * @return true
 * @return false
 */
bool updateBook(LIST &lst, string name, Book newBook)
{
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
bool removeBook(LIST &lst, string name)
{
    if (lst.head == NULL)
    {
        return false;
    }

    if (lst.head->info.name == name)
    {
        Node *p = lst.head;
        lst.head = lst.head->next;
        delete p;
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
            return true;
        }
        prev = p;
        p = p->next;
    }
    return false;
}
/**
 * @brief Search By Name
 *
 * @param list
 * @param name
 */
void searchByName(LIST &list, string name)
{
    Node *p = list.head;
    bool found = false;
    while (p != NULL)
    {
        if (p->info.name == name)
        {
            cout << "Found: " << p->info.name << ", " << p->info.quantity << ", " << p->info.price << endl;
            found = true;
        }
        p = p->next;
    }
    if (!found)
    {
        cout << "Not found." << endl;
    }
}
/**
 * @brief Search By Price
 *
 * @param list
 * @param price
 */
void searchByPrice(LIST &list, int price)
{
    Node *p = list.head;
    bool found = false;
    while (p != NULL)
    {
        if (p->info.price == price)
        {
            cout << "Found: " << p->info.name << ", " << p->info.quantity << ", " << p->info.price << endl;
            found = true;
        }
        p = p->next;
    }
    if (!found)
    {
        cout << "Not found." << endl;
    }
}
/**
 * @brief Sort By Name of Book
 *
 * @param lst
 */
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
void sortListByTotalAmount(DLIST &list)
{
    if (list.head == nullptr || list.head == list.tail)
    {
        return;
    }

    DNode *curr = list.head->next;
    while (curr != nullptr)
    {
        Customer tmp = curr->info;
        DNode *prev = curr->prev;

        while (prev != nullptr && prev->info.bill > tmp.quantity)
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
/**
 * @brief Find Max by Price
 *
 * @param list
 * @return Books
 */
Book findMaxByPrice(LIST list)
{
    if (list.head == nullptr)
    {
        return Book{"", 0, 0, 0};
    }

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

    return maxBook;
}
/**
 * @brief Find Min By Price
 *
 * @param list
 * @return Book
 */
Book findMinByPrice(LIST list)
{
    if (list.head == nullptr)
    {
        return Book{"", 0, 0, 0};
    }

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

    return minBook;
}
// Hàm tính tổng giá trị của các sản phẩm
int sum(LIST list)
{
    int sum = 0;
    Node *p = list.head;
    while (p != NULL)
    {
        sum += p->info.price;
        p = p->next;
    }
    return sum;
}

// Hàm tính trung bình giá trị của các sản phẩm
float average(LIST list)
{
    if (list.head == NULL)
    {
        return 0;
    }
    int sum = 0, count = 0;
    Node *p = list.head;
    while (p != NULL)
    {
        sum += p->info.price;
        count++;
        p = p->next;
    }
    return (float)sum / count;
}

// Hàm đếm số lượng sản phẩm trong danh sách
int count(LIST list)
{
    int count = 0;
    Node *p = list.head;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }
    return count;
}

// Hàm tính tổng giá trị của các sản phẩm có kích cỡ nhỏ hơn một giá trị cho trước
int sumBySize(LIST list, int sizeLimit)
{
    int sum = 0;
    Node *p = list.head;
    while (p != NULL)
    {
        if (p->info.type < sizeLimit)
        {
            sum += p->info.price;
        }
        p = p->next;
    }
    return sum;
}

// Hàm tính số lượng sản phẩm có giá trị lớn hơn một giá trị cho trước
int countByPrice(LIST list, int priceLimit)
{
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
    return count;
}

void displayClothing(LIST lst)
{
    cout << "List of clothing: " << endl;
    Node *p = lst.head;
    while (p != NULL)
    {
        cout << "Name: " << p->info.name << ", Size: " << p->info.type << ", Price: " << p->info.price << endl;
        p = p->next;
    }
}

void inputClothingList(LIST &lst)
{
    int n;
    cout << "Enter the number of clothing items: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        Book book;
        cout << "Enter clothing item #" << i + 1 << ":" << endl;
        cout << "Name: ";
        cin >> book.name;
        cout << "Type: ";
        cin >> book.type;
        cout << "Price: ";
        cin >> book.price;
        addBook(lst, book);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////// Hóa đơn
/**
 *
 *
 *
 *
 *
 * //////////////////////////////////////////////////////////////////////////////////////////////////
 *
 *
 *
 *
 * /////////////////////////////////////////////////////////////////////////////////////////////
 * */

void addInvoice(DLIST &dlst, Customer inv)
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

// Hàm cập nhật thông tin của một đối tượng Hóa đơn trong danh sách
bool updateInvoice(DLIST &lst, string customerName, Customer newIn)
{
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

// Hàm xóa một đối tượng Hóa đơn trong danh sách
bool removeInvoice(DLIST &lst, string customerName)
{
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

DNode *searchInvoice(DLIST DQ, char *customer_name)
{
    DNode *p;
    p = DQ.head;
    while (p != NULL)
    {
        if (p->info.customerName == customer_name)
            break;
        p = p->next;
    }
    return p;
}

Customer findMaxByTotalAmount(DLIST list)
{
    // Trường hợp danh sách rỗng
    if (list.head == nullptr)
    {
        return Customer{"", 0, 0};
    }

    // Duyệt danh sách liên kết kép từ đầu đến cuối để tìm phần tử lớn nhất
    DNode *curr = list.head;
    Customer maxInvoice = curr->info;
    while (curr != nullptr)
    {
        if (curr->info.bill > maxInvoice.bill)
        {
            maxInvoice = curr->info;
        }
        curr = curr->next;
    }

    return maxInvoice;
}

Customer findMinTotalAmount(DLIST list)
{
    // Trường hợp danh sách rỗng
    if (list.head == nullptr)
    {
        return Customer{"", 0, 0};
    }

    // Duyệt danh sách liên kết kép từ đầu đến cuối để tìm phần tử nhỏ nhất
    DNode *curr = list.head;
    Customer minInvoice = curr->info;
    while (curr != nullptr)
    {
        if (curr->info.bill < minInvoice.bill)
        {
            minInvoice = curr->info;
        }
        curr = curr->next;
    }

    return minInvoice;
}

// Tính tổng của trường totalAmount của các Invoice trong danh sách liên kết kép
int getTotal(DLIST list)
{
    // Trường hợp danh sách rỗng
    if (list.head == nullptr)
    {
        return 0;
    }

    // Duyệt danh sách liên kết kép từ đầu đến cuối để tính tổng
    DNode *curr = list.head;
    int total = 0;
    while (curr != nullptr)
    {
        total += curr->info.bill;
        curr = curr->next;
    }

    return total;
}

// Tính trung bình của trường totalAmount của các Invoice trong danh sách liên kết kép
float getAverage(DLIST list)
{
    // Trường hợp danh sách rỗng
    if (list.head == nullptr)
    {
        return 0;
    }

    // Tính tổng và đếm số lượng phần tử trong danh sách liên kết kép
    int total = 0;
    int count = 0;
    DNode *curr = list.head;
    while (curr != nullptr)
    {
        total += curr->info.bill;
        count++;
        curr = curr->next;
    }

    // Tính trung bình và trả về kết quả
    return (float)total / count;
}

// Đếm số lượng phần tử trong danh sách liên kết kép
int getCount(DLIST list)
{
    // Trường hợp danh sách rỗng
    if (list.head == nullptr)
    {
        return 0;
    }

    // Duyệt danh sách liên kết kép từ đầu đến cuối để đếm số lượng phần tử
    int count = 0;
    DNode *curr = list.head;
    while (curr != nullptr)
    {
        count++;
        curr = curr->next;
    }

    return count;
}

// Thống kê những hóa đơn có totalAmount lớn hơn 50000
void findLargeInvoices(DLIST list)
{
    DNode *p = list.head;
    bool found = false;
    cout << "Cac hoa don co gia tri lon hon 50000:" << endl;
    while (p != NULL)
    {
        if (p->info.bill > 50000)
        {
            found = true;
            cout << "Hoa don cua khach hang " << p->info.customerName << " co gia tri " << p->info.bill << endl;
        }
        p = p->next;
    }
    if (!found)
    {
        cout << "Khong co hoa don nao co gia tri lon hon 50000." << endl;
    }
}

// Thống kê Khách hàng A mua bao nhiêu sản phẩm
int countProductByCustomerName(DLIST *list, string customerName)
{
    int count = 0;
    DNode *p = list->head;
    while (p != NULL)
    {
        if (p->info.customerName == customerName)
        {
            count += p->info.quantity;
        }
        p = p->next;
    }
    return count;
}

void displayInvoice(DLIST dlst)
{
    cout << "List of invoices: " << endl;
    DNode *p = dlst.head;
    while (p != NULL)
    {
        cout << "Customer name: " << p->info.customerName << ", Total amount: " << p->info.quantity << ", Quantity: "
             << p->info.bill << endl;
        p = p->next;
    }
}

void inputInvoiceList(DLIST &lst)
{
    int n;
    cout << "Enter the number of invoices: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        Customer inv;
        cout << "Enter invoice #" << i + 1 << ":" << endl;
        cout << "Customer name: ";
        cin >> inv.customerName;
        cout << "Quantity: ";
        cin >> inv.quantity;
        cout << "Bill: ";
        cin >> inv.bill;
        addInvoice(lst, inv);
    }
}

int main()
{
    LIST bookList;
    DLIST customerList;
    bookList.head = NULL;
    customerList.tail = NULL;
    bookList.head = NULL;
    customerList.tail = NULL;

    bool continue_program = true;
    while (continue_program)
    {
        int choice = 0;
        cout << "Menu chon chuong trinh: " << endl;
        cout << "1. Lua chon so 1" << endl;
        cout << "2. Lua chon so 2" << endl;
        cout << "3. Lua chon so 3" << endl;
        cout << "4. Lua chon so 4" << endl;
        cout << "5. Lua chon so 5" << endl;
        cout << "6. Lua chon so 6" << endl;
        cout << "7. Lua chon so 7" << endl;
        cout << "8. Lua chon so 8" << endl;
        cout << "Nhap lua chon cua ban: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Ban da chon lua chon so 1" << endl;
            bool continue_choice1 = true;
            while (continue_choice1)
            {
                int sub_choice = 0;
                cout << "1.1. Lua chon chuc nang A" << endl;
                cout << "1.2. Lua chon chuc nang B" << endl;
                cout << "1.3. Quay lai menu chinh" << endl;
                cout << "Nhap lua chon cua ban: ";
                cin >> sub_choice;
                switch (sub_choice)
                {
                case 1:
                    cout << "Ban da chon chuc nang A" << endl;
                    // Viết code để thực hiện chức năng A ở đây
                    break;
                case 2:
                    cout << "Ban da chon chuc nang B" << endl;
                    // Viết code để thực hiện chức năng B ở đây
                    break;
                case 3:
                    cout << "Quay lai menu chinh" << endl;
                    continue_choice1 = false; // set biến flag thành false để kết thúc vòng lặp while
                    break;
                default:
                    cout << "Lua chon khong hop le, vui long chon lai" << endl;
                    break;
                }
            }
            break;
            // case 2:
            //     cout << "Ban da chon lua chon so 2" << endl;
            //     // Viết code để thực hiện chức năng C ở đây
            //     break;
            // case 3:
            //     cout << "Ban da chon lua chon so 3" << endl;
            //     // Viết code để thực hiện chức năng D ở đây
            //     break;
            // case 4:
            //     cout << "Ban da chon lua chon so 4" << endl;
            //     // Viết code để thực hiện chức năng E ở đây
            //     break;
            // case 5:
            //     cout << "Ban da chon lua chon so 5" << endl;
            //     // Viết code để thực hiện chức năng F ở đây
            //     break;
            // case 6:
            //     cout << "Ban da chon lua chon so 6" << endl;
            //     // Viết code để thực hiện chức năng G ở đây
            //     break;
            // case 7:
            //     cout << "Ban da chon lua chon so 7" << endl;
            //     break;
            // case 8:
            //     cout << "Ban da chon lua chon so 8" << endl;
            //     // Viết code để thực hiện chức năng I ở đây
            //     break;
            // default:
            //     cout << "Lua chon khong hop le" << endl;
            //     break;
        }
    }

    // chuc năng
    //    inputClothingList(clothingList);
    //    inputInvoiceList(invoiceList);
    //    displayClothing(clothingList);
    //    displayInvoice(invoiceList);

    return 0;
}