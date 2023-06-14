#include<iostream>

using namespace std;
// Đồng Duy Thường Thiết kế Danh sách liên kết 
//
struct Node {
    int data;       // Giá trị được lưu trữ trong nút
    Node* next;     // Con trỏ đến nút tiếp theo. Khai báo kiểu đệ quy.
};
//Khởi tạo node
Node* KhoitaoNode(int du_lieu0)     // du_lieu là khởi tạo giá trị ban đầu cho nút mới
{
    Node* node = new Node;          //tạo node mới và cấp phát bộ nhớ động cho node
    node->data = du_lieu0;          //khởi gán giá trị dữ liệu ban đầu du_lieu
    node->next = NULL;              //nút mới tạo chưa trỏ vào đâu cả nên next=NULL
    return node;                    // trả về nút mới tạo
}
//Khai báo kiểu cấu trúc danh sách liên kết
struct List
{
    Node* head;
    Node* tail;
};
//Hàm khởi tạo danh sách liên kết rỗng ban đầu
void KhoiTaoList(List& list)
{
    list.head = NULL;               //Lúc đầu danh sách rỗng head và tail chưa trỏ vào đâu cả

    list.tail = NULL;                // được gán NULL

}
//Thêm nút vào danh sách liên kết
void ThemvaoDau(List& list, Node* node)
{
    if (list.head == NULL)
    {
        list.head = node;
        list.tail = node;
    }
    else

    {
        node->next = list.head;
        list.head = node;
    }

}
//Thêm nút vào cuối danh sách liên kết

void ThemvaoCuoi(List& list, Node* node)
{
    if (list.head == NULL)
    {
        list.head = node;
        list.tail = node;
    }

    else {
        list.tail->next = node;         //next của tail trỏ vào node
        list.tail = node;               //node đóng vai trò tail }

    }
}
    //Thêm node vào sau nút k(k là tên nút chứ không phải là số thứ tự)
    void ThemNutSauK(List & list, Node * node, Node * k) {
        if (k != NULL) {
            node->next = k->next;
            k->next = node;
            if (list.tail == k)
                list.tail = node;
        }
        else {
            ThemvaoCuoi(list, node);  // Nếu k==null thì thêm vào cuối danh sách
        }

    }
//Xóa node ở đầu
    int XoaNutDau(List& list, int& a)
    {
        if (list.head != NULL) 

        {
            Node* node = list.head; //lưu lại nút đầu
            a = node->data; //lấy dữ liệu của nút sẽ bị xóa
            list.head = node->next; //đầu mới của danh sách sẽ là nút kế tiếp nút đầu
            delete node; //xóa nút lưu nút đầu
            if (list.head == NULL) list.tail = NULL;
            return 1;
        }
        return 0;
    }
//Xóa nút sau một nút k xác định(k là tên nút chứ không phải chỉ số nút) -- Làm thêm
    int XoaNutSauK(List& list, Node* k, int& a)
    {
        if (k != NULL)
        {
            Node* node = k->next; // node là nút sau k
            if (node != NULL)
            {
                if (list.tail == node) list.tail = k;
                k->next = node->next;
                a = node->data;
                delete node;
                return 1;

            }
            return 0;
        }
        return 0;
    }
// Xóa các node có giá trị bằng a cho trước và trả về nố nút đã xóa
    int XoaPhanTu(List& list, int a)
    {
        int count = 0; // Biến đếm số phần tử đã xóa

        while (list.head != NULL && list.head->data == a) {
            Node* node = list.head;
            list.head = list.head->next;
            delete node;
            count++;
        }

        if (list.head == NULL) {
            list.tail = NULL;
            return count;
        }

        Node* current = list.head;
        while (current->next != NULL) {
            if (current->next->data == a) {
                Node* node = current->next;
                current->next = node->next;
                delete node;
                count++;
            }
            else {
                current = current->next;
            }
        }

        list.tail = current;
        return count;
    }

// Hiển thị danh sách
        void HienDS(List list)
        {
            if (list.head != NULL)
            {
                Node* node = list.head;
                while (node != NULL)

                {
                    cout << node->data << " ";
                    node = node->next;
                }

            }
        }
// Hiển thị node bất kì theo chỉ số
        Node* HienNut(List& list, int chi_so) // tìm và hiện nút theo chỉ số
        {
            Node* node = list.head;
            int i = 0;
            while (node != NULL && i != chi_so)
            {
                node = node->next; i++;
            }
            if (i == chi_so && node != NULL)
                return node;
            return NULL;
        }
//Tìm kiếm phần tử trong danh sách theo dữ liệu
        Node* TimNut(List& list, int a) //tìm theo dữ liệu
        {
            Node* node = list.head;
            while (node != NULL && node->data != a) node = node->next;
            if (node != NULL) return node;
            return NULL;
        }
//Đếm số phần tử của danh sách
        int Count(List& list) {
            int n = 0;
            Node* node = list.head;
            while (node != NULL) { n++; node = node->next; }
            return n;
        }
//Xóa danh sách
          
        void XoaDS(List & list)
        {
            int a;
            Node* node = list.head;
            while (node != NULL) {
                XoaNutDau(list, a);
                node = list.head;
            }

            list.tail = NULL;
        }
// Hàm trộn hai danh sách liên kết sắp xếp tăng dần thành một danh sách mới - Giống Merge sort
        List MergeLists(List list1, List list2)
        {
            List mergedList;
            KhoiTaoList(mergedList);

            Node* current1 = list1.head;
            Node* current2 = list2.head;

            while (current1 != NULL && current2 != NULL)
            {
                if (current1->data <= current2->data)
                {
                    Node* newNode = KhoitaoNode(current1->data);
                    ThemvaoCuoi(mergedList, newNode);
                    current1 = current1->next;
                }
                else
                {
                    Node* newNode = KhoitaoNode(current2->data);
                    ThemvaoCuoi(mergedList, newNode);
                    current2 = current2->next;
                }
            }

            // Thêm các nút còn lại của danh sách 1 (nếu có)
            while (current1 != NULL)
            {
                Node* newNode = KhoitaoNode(current1->data);
                ThemvaoCuoi(mergedList, newNode);
                current1 = current1->next;
            }

            // Thêm các nút còn lại của danh sách 2 (nếu có)
            while (current2 != NULL)
            {
                Node* newNode = KhoitaoNode(current2->data);
                ThemvaoCuoi(mergedList, newNode);
                current2 = current2->next;
            }

            return mergedList;
        }
// Trộn 32 List lại tạo ra 1 danh sách liên kết tổng hợp
        List Merge32Lists(List lists[], int numLists)
        {
            while (numLists > 1)
            {
                int startIndex = 0;
                int endIndex = numLists - 1;

                while (startIndex < endIndex)
                {
                    lists[startIndex] = MergeLists(lists[startIndex], lists[endIndex]);
                    // Tận dụng hàm trộn 2 List ở trên.
                    startIndex++;
                    endIndex--;
                }

                if (startIndex >= endIndex)
                    numLists = startIndex;
            }

            return lists[0];
        }

//MAIN 
        int main() {
            List list1;
            KhoiTaoList(list1);
            /*  Kiểm tra khởi tạo List và các hàm  */
            // Thêm nút vào danh sách
            Node* node1 = KhoitaoNode(5);
            ThemvaoDau(list1, node1);

            Node* node2 = KhoitaoNode(10);
            ThemvaoDau(list1, node2);

            Node* node3 = KhoitaoNode(15);
            ThemvaoCuoi(list1, node3);

            // Hiển thị danh sách
            cout << "Danh sach: ";
            HienDS(list1);
            cout << endl;

            // Xóa nút đầu danh sách
            int a;
            XoaNutDau(list1, a);
            cout << "Da xoa nut dau. Gia tri xoa: " << a << endl;

            // Xóa nút sau nút đầu danh sách
            Node* node = HienNut(list1, 0);
            XoaNutSauK(list1, node, a);
            cout << "Da xoa nut sau nut dau. Gia tri xoa: " << a << endl;

            // Xóa các nút có giá trị bằng 10
            int count = XoaPhanTu(list1, 10);
            cout << "Da xoa " << count << " nut co gia tri 10" << endl;

            // Hiển thị danh sách sau khi xóa
            cout << "Danh sach sau khi xoa: ";
            HienDS(list1);
            cout << endl;

            // Tìm nút theo dữ liệu cho trước 
            Node* nodeToFind = TimNut(list1, 15);
            if (nodeToFind != NULL) {
                cout << "Tim thay nut co gia tri 15" << endl;
            }
            else {
                cout << "Khong tim thay nut co gia tri 15" << endl;
            }

            // Đếm số phần tử trong danh sách
            int countNodes = Count(list1);
            cout << "So phan tu trong danh sach: " << countNodes << endl;

            // Xóa danh sách
            XoaDS(list1);
            /*  Thuật toán tương đối giống Merge sort  */

            List list2;
            KhoiTaoList(list2);
            /*  Kiểm tra khởi tạo List và các hàm  */
            // Thêm nút vào danh sách
            Node* node4 = KhoitaoNode(6);
            ThemvaoDau(list2, node4);

            Node* node5 = KhoitaoNode(9);
            ThemvaoDau(list2, node5);

            Node* node6 = KhoitaoNode(18);
            ThemvaoCuoi(list2, node6);

            // Hiển thị danh sách
            cout << "Danh sach: ";
            HienDS(list2);
            cout << endl;
            /*
            * Khởi tạo đầy đủ 32 danh sách liên kết đơn thỏa mãn tính chất tăng dần dữ liệu .
            * List lists[32];           Tạo mảng lists với 32 danh sách.
            * Khởi tạo các danh sách liên kết đơn từ lists[0] -> [31]
            * List mergedList = Merge32Lists(lists, 32);
            * HienDS(mergedList);
            */
            return 0;
        }
