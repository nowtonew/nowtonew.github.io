#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>

#define MAX 1000

using namespace std;

// 联系人结构体
struct Person
{
    string name;
    string phone;
    string sex;
    int age;
    string address;
};

// 通讯录结构体
struct Addressbook
{
    struct Person a_Person[MAX];
    int a_number;
};

// 功能菜单
void showMenu()
{
    cout << "***********************" << endl;
    cout << "***** 1.新建联系人 *****" << endl;
    cout << "***** 2.显示联系人 *****" << endl;
    cout << "***** 3.删除联系人 *****" << endl;
    cout << "***** 4.查找联系人 *****" << endl;
    cout << "***** 5.修改联系人 *****" << endl;
    cout << "***** 6.清空联系人 *****" << endl;
    cout << "***** 0.退出通讯录 *****" << endl;
    cout << "***********************" << endl;
}

// 新建联系人
void addPerson(Addressbook *ads) // 用具体的结构体指针来接收结构体的地址
{
    int i = ads->a_number;
    if (i == MAX)
    {
        cout << "通讯录已满，新增联系人功能不可用" << endl;
    }
    else
    {
        cout << "请输入联系人姓名：" << endl;
        cin >> ads->a_Person[i].name;
        cout << "请输入联系人电话：" << endl;
        cin >> ads->a_Person[i].phone;
        cout << "请输入联系人性别：" << endl;
        cin >> ads->a_Person[i].sex;
        cout << "请输入联系人年龄：" << endl;
        cin >> ads->a_Person[i].age;
        cout << "请输入联系人家庭住址：" << endl;
        cin >> ads->a_Person[i].address;
        cout << "新增联系人成功！" << endl;
        ads->a_number++;
    }
}

// 显示通讯录列表
void showPerson(Addressbook *ads)
{
    int i = ads->a_number;
    if (i == 0)
    {
        cout << "通讯录为空！" << endl;
    }
    else
    {
        for (int j = 0; j < i; j++)
        {
            cout << "姓名：" << ads->a_Person[j].name << '\t';
            cout << "电话：" << ads->a_Person[j].phone << '\t';
            cout << "性别：" << ads->a_Person[j].sex << '\t';
            cout << "年龄：" << ads->a_Person[j].age << '\t';
            cout << "住址：" << ads->a_Person[j].address << endl;
        }
    }
}

// 检测联系人是否存在
int existPerson(Addressbook *ads, string name)
{
    int i = ads->a_number;
    for (int j = 0; j < i; j++)
    {
        if (ads->a_Person[j].name == name)
        {
            return j;
        }
    }
    return -1;
}

// 删除联系人
void delPerson(Addressbook *ads)
{
    int i = ads->a_number;
    int tag = 0;
    string n = "";
    cout << "请输入要删除的联系人姓名" << endl;
    cin >> n;
    tag = existPerson(ads, n);
    if (tag < 0)
    {
        cout << "联系人不存在！" << endl;
    }
    else if (tag == i - 1)
    {
        ads->a_number--;
        cout << "删除联系人成功！" << endl;
    }
    else
    {
        for (; tag < i - 1; tag++)
        {
            ads->a_Person[tag] = ads->a_Person[tag + 1];
        }
        ads->a_number--;
        cout << "删除联系人成功！" << endl;
    }
}

// 查找联系人
void findPerson(Addressbook *ads)
{
    int tag = 0;
    string n = "";
    cout << "请输入您想要查找的联系人姓名：" << endl;
    cin >> n;
    tag = existPerson(ads, n);
    if (tag < 0)
    {
        cout << "您想要查找的联系人不存在" << endl;
    }
    else
    {
        cout << "已为您查找到对应联系人信息：" << endl;
        cout << "姓名：" << ads->a_Person[tag].name << '\t';
        cout << "电话：" << ads->a_Person[tag].phone << '\t';
        cout << "性别：" << ads->a_Person[tag].sex << '\t';
        cout << "年龄：" << ads->a_Person[tag].age << '\t';
        cout << "住址：" << ads->a_Person[tag].address << endl;
    }
}

// 修改联系人信息
void editPerson(Addressbook *ads)
{
    int tag = 0;
    string n = "", s = "", a = "";
    cout << "请输入想要修改的联系人姓名：" << endl;
    cin >> n;
    tag = existPerson(ads, n);
    if (tag < 0)
    {
        cout << "联系人不存在！" << endl;
    }
    else
    {
        cout << "当前联系人信息为：" << endl;
        cout << "姓名：" << ads->a_Person[tag].name << '\t';
        cout << "电话：" << ads->a_Person[tag].phone << '\t';
        cout << "性别：" << ads->a_Person[tag].sex << '\t';
        cout << "年龄：" << ads->a_Person[tag].age << '\t';
        cout << "住址：" << ads->a_Person[tag].address << endl;
        cout << "-----------------------------------" << endl;
        cout << "请输入修改后的联系人姓名：" << endl;
        cin >> ads->a_Person[tag].name;
        cout << "请输入修改后的联系人电话：" << endl;
        cin >> ads->a_Person[tag].phone;
        cout << "请输入修改后的联系人性别：" << endl;
        cin >> ads->a_Person[tag].sex;
        cout << "请输入修改后的联系人年龄：" << endl;
        cin >> ads->a_Person[tag].age;
        cout << "请输入修改后的联系人住址：" << endl;
        cin >> ads->a_Person[tag].address;
        cout << "联系人信息修改成功！" << endl;
        cout << "-----------------------------------" << endl;
        cout << "以下为修改后的联系人信息：" << endl;
        cout << "姓名：" << ads->a_Person[tag].name << '\t';
        cout << "电话：" << ads->a_Person[tag].phone << '\t';
        cout << "性别：" << ads->a_Person[tag].sex << '\t';
        cout << "年龄：" << ads->a_Person[tag].age << '\t';
        cout << "住址：" << ads->a_Person[tag].address << endl;
    }
}
// 清空通讯录

void delAddressbook(Addressbook *ads)
{
    ads->a_number = 0;
    cout << "通讯录已清空！" << endl;
}

// int main()
// {
//     Addressbook ads;
//     ads.a_number = 0;
//     int select = 10;
//     while (true)
//     {
//         showMenu();
//         cout << "请输入您想选择的功能序号：" << endl;
//         cin >> select;
//         switch (select)
//         {
//         case 1: // 新建联系人
//             addPerson(&ads);
//             break;
//         case 2: // 显示联系人
//             showPerson(&ads);
//             break;
//         case 3: // 删除联系人
//             delPerson(&ads);
//             break;
//         case 4: // 查找联系人
//             findPerson(&ads);
//             break;
//         case 5: // 修改联系人
//             editPerson(&ads);
//             break;
//         case 6: // 清空联系人
//             delAddressbook(&ads);
//             break;
//         case 0: // 退出通讯录
//             cout << "退出通讯录成功!" << endl;
//             return 0;
//             break;
//         }
//     }
// }
