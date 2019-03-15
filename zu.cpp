/*
 *宾馆的客房信息包括客房号、客房类型、客房价格、空闲情况、客人姓名、客人身份证号、入住时间、退房时间，预付费用等信息。
 *试设计一宾馆客房管理系统统，系统以菜单方式工作，使之能提供以下功能：
 *客房信息的录入功能
 *客人入住登记
 *客人退房结算
 *客房信息浏览功能，浏览全部客房的信息
 *客房信息查询：查询空房间情况、按姓名或房间号查询
 *客房信息的删除、修改功能
 *本地存储房间和房客信息
 */

#include <iostream>
#include <ctime>
#include <cstdio>
#include<fstream>
using namespace std;

static int No_Room = 0;                             //房间id，用于统计房间数量
static int No_Fangke = 0;                           //用于统计房客数量
struct Room
{
    int Room_num;                                   //房间号
    string Room_type;                               //房间类型
    double Room_price;                              //房间价格
    bool iskongxian = true;                         //是否空闲
    string name = "";                               //房客姓名
} *room = new Room[20];

struct Fangke
{
    string name;                                    //客人姓名
    string idcard;                                  //客人身份证号码
    int Room_num = 0;                               //入住房间号
    string update;                                  //入住时间
    string tuidate = "0";                            //退房时间
    double yajin;                                   //预付费用

} *fangke = new Fangke[50];



void create(Room *r);                               //创建房间
void delroom(Room *r);                              //删除房间
void look(Room *r, Fangke *f);                      //查看所有房间
void look(Room *r, Fangke *f, int num);             //根据房间号查看该房间
void look(Room *r, Fangke *f, string name);         //根据房客信息查找房间

void create(Fangke *f, Room *r);                    //创建房客
void create(Fangke *f, string name, int num);       //从创建房间那创建房客
void look_fangke(Room *r, Fangke *f);               //查询所有房客
void look_fangke(Room *r, Fangke *f, string idcard); //根据证件号码查询房客
void look_fangke1(Room *r, Fangke *f, string name);  //根据房客姓名查询房客
void tuif(Fangke *f, Room *r);                      //退房

void update_text(Room *r, Fangke *f);                //重新写入数据
int main()
{
    ifstream r;
    r.open("Room",ios::in);
    while(r.peek() != EOF)
    {
        r>>room[No_Room].Room_num>>room[No_Room].Room_type>>room[No_Room].Room_price>>room[No_Room].iskongxian;
        ++No_Room;
    }
    r.close();

    ifstream f;
    f.open("fangke",ios::in);
    while(f.peek() != EOF)
    {

        f >> fangke[No_Fangke].idcard >> fangke[No_Fangke].name >> fangke[No_Fangke].Room_num >> fangke[No_Fangke].yajin >> fangke[No_Fangke].update >> fangke[No_Fangke].tuidate;
        ++No_Fangke;
    }
    f.close();

    char shuru = 0;
    while(shuru != 'q')
    {
        system("pause");
        system("cls");
        cout << "1、创建房间\n"
         << "2、删除房间\n"
         << "3、查看房间\n"
         << "4、登记入住\n"
         << "5、退房\n"
         << "6、查询房客\n"
         << "q、退出系统\n";
        cin >> shuru;
        system("cls");
        string test;
        getline(cin, test);
        switch(shuru)
        {
            case '1':                           //创建房间
                cout << "-----------创建房间---------" << endl;
                create(room);
                break;
            case '2':                           //删除房间
            {
                cout << "-----------删除房间---------" << endl;
                delroom(room);
                break;
            }
            case '3':                           //查看房间
            {
                cout << "-----------查看房间---------" << endl;
                cout << "1、查看所有房间\n"
                    << "2、根据房间号查看该房间\n";
                char look_type;
                cin >> look_type;
                switch(look_type)
                {
                    case '1':
                        look(room, fangke);
                        break;
                    case '2':
                    {
                        cout << "请输入房间号:";
                        int num;
                        cin >> num;
                        look(room, fangke, num);
                        break;
                    }
                    default:
                        cout << "输入错误！" << endl;
                }
                break;
            }
            case '4':                           //登记入住
                cout << "-----------登记入住---------" << endl;
                create(fangke,room);
                break;
            case '5':                           //退房
                cout << "-----------退房---------" << endl;
                tuif(fangke,room);
                break;
            case '6':
            {
                cout << "-----------查询房客---------" << endl;
                cout << "1、查询所有房客\n"
                     << "2、根据房客姓名查询房客\n"
                     << "3、根据身份证号码查询房客\n";
                char look_type;
                cin >> look_type;
                switch(look_type)
                {
                    case '1':
                        look_fangke(room, fangke);
                        break;
                    case '2':
                    {
                        cout << "请输入客户姓名:";
                        string name;
                        cin >> name;
                        look_fangke1(room, fangke, name);
                        break;
                    }
                    case '3':
                    {
                        cout << "请输入身份证号码:";
                        string idcard;
                        cin.get();
                        getline(cin, idcard);
                        look_fangke(room, fangke, idcard);
                        break;
                    }
                    default:
                        cout << "输入错误！" << endl;
                }
                break;
            }

            case 'q':                           //退出系统
                update_text(room, fangke);
                break;
            default:
                cout << "输入错误！" << endl;
        }
    }
    delete[] room;
    delete[] fangke;
    return 0;
}

void create(Room *r)
{
    int i = No_Room;
    int num;
    cout << "房间号 : ";
    cin >> num;
    for (int len = 0; len < No_Room; ++len)
    {
        if(r[len].Room_num==num)
        {
            cout << "已存在该房间" << endl;
            return;
        }
    }
    r[i].Room_num = num;
    cout << endl
         << "房间类型 : ";
    cin >> r[i].Room_type;
    cout << endl
         << "房间价格 : ";
    cin >> r[i].Room_price;
    cout << endl
         << "是否为空闲房间(Y/N)？";
    char is;
    cin >> is;
    if (is != 'Y')
    {
        cout << endl
             << "请输入房客姓名 :";
        cin.get();
        getline(cin, r[i].name);
        create(fangke, r[i].name, r[i].Room_num);
    }

    ++No_Room;
    cout << "房间创建成功！" << endl;
}

void delroom(Room *r)
{
    cout << "请输入你要删除的房间号 : ";
    int num;
    cin >> num;
    bool flag = false;
    for (int i = 0; i < No_Room; ++i)
    {
        if(r[i].Room_num == num)
        {
            flag = true;
            if(!r[i].iskongxian)
            {
                cout << "需要删除的房间不为空闲状态，无法删除！" << endl;
                break;
            }
            else
            {
                for (int delen = i; delen < No_Room - 1; ++delen)
                {
                    r[delen].Room_num = r[delen + 1].Room_num;
                    r[delen].Room_type = r[delen + 1].Room_type;
                    r[delen].Room_price = r[delen + 1].Room_price;
                    r[delen].iskongxian = r[delen + 1].iskongxian;
                }
                r[No_Room - 1].Room_num = 0;
                r[No_Room - 1].Room_type = "";
                r[No_Room - 1].Room_price = 0;
                r[No_Room - 1].iskongxian = true;
                --No_Room;
                cout << "删除成功！" << endl;
                break;
            }
        }
    }
    if(!flag)
        cout << "没有找到该房间！" << endl;
}

void look(Room *r, Fangke *f)
{
    if (No_Room == 0)
    {
        cout << "您目前没有可以出租的房间" << endl;
        return;
    }
    for (int i = 0; i < No_Room; ++i)
    {
        cout << "房间号：" << r[i].Room_num << endl
             << "房间类型：" << r[i].Room_type << endl
             << "房间价格：" << r[i].Room_price << endl;
        if(!r[i].iskongxian)
        {
            for (int j = No_Fangke - 1; j >= 0; --j)
            {
                if(r[i].Room_num == f[j].Room_num)
                {
                    cout << "房客信息：" << f[j].name << endl
                            << "证件号码：" << f[j].idcard << endl
                            << "入住时间：" << f[j].update << endl
                            << "预付费用：" << f[j].yajin << endl;
                    break;
                }
            }
        }
        else
            cout << "空房间，暂无房客居住。" << endl;
        cout << "---------------------------------------------" << endl;
    }
}

void look(Room *r, Fangke *f, int num)
{
    bool flag = false;
    for (int i = 0; i < No_Room;++i)
    {
        if(r[i].Room_num == num)
        {
            flag = true;
            cout << "房间号：" << r[i].Room_num << endl
                 << "房间类型：" << r[i].Room_type << endl
                 << "房间价格：" << r[i].Room_price << endl;
            if(!r[i].iskongxian)
            {
                for (int j = No_Fangke - 1; j >= 0; --j)
                {
                    if(r[i].Room_num == f[j].Room_num)
                    {
                        cout << "房客信息：" << f[j].name << endl
                                << "证件号码：" << f[j].idcard << endl
                                << "入住时间：" << f[j].update << endl
                                << "预付费用：" << f[j].yajin << endl;
                        break;
                    }
                }
            }
            else
                cout << "空房间，暂无房客居住。" << endl;
            cout << "---------------------------------------------" << endl;
        }
    }
    if(!flag)
        cout << "没有找到该房间！" << endl;
}

void look(Room *r, Fangke *f, string name)
{
    bool flag = false;
    for (int i = 0; i < No_Room;++i)
    {
        if(r[i].name == name)
        {
            flag = true;
            cout << "房间号：" << r[i].Room_num << endl
                 << "房间类型：" << r[i].Room_type << endl
                 << "房间价格：" << r[i].Room_price << endl;
                for (int j = 0; j < No_Fangke;++j)
                {
                    if(r[i].Room_num == f[j].Room_num)
                    {
                        cout << "房客信息：" << f[j].name << endl
                                << "证件号码：" << f[j].idcard << endl
                                << "入住时间：" << f[j].update << endl
                                << "预付费用：" << f[j].yajin << endl;
                    }
                }
            cout << "---------------------------------------------" << endl;
            break;
        }
    }
    if(!flag)
        cout << "该房客没有入住！" << endl;
}

void create(Fangke *f, Room *r)
{
    int i = No_Fangke;
    bool flag = false;
    string idcard;
    time_t now = time(0);
    tm *ltm = localtime(&now);
    cout << "房客姓名 : ";

    getline(cin, f[i].name);
    cout << endl
         << "客人身份证号码 : ";
    getline(cin, idcard);
    if (No_Fangke != 0)
    {
        for (int j = 0; j < No_Fangke; ++j)
        {
            if(f[j].idcard==idcard && f[j].name != f[i].name)
            {
                cout << "该身份证号码已存在！";
                return;
            }
            if (f[j].idcard == idcard && f[j].tuidate == "0")
            {
                cout << "该客户以入住:" << f[j].Room_num << "是否还要入住其他房间？(Y/N)" << endl;
                char is;
                cin >> is;
                if(is!='Y')
                    return;
            }
        }
    }
    f[i].idcard = idcard;
    cout << endl
         << "入住房间号 : ";
    cin >> f[i].Room_num;
    for (int len = 0; len < No_Room; ++len)
    {
        if (f[i].Room_num == r[len].Room_num)
        {
            flag = true;
            if(!r[len].iskongxian)
            {
                cout << "该房间不是空闲房间!" << endl;
                cout << "创建失败！" << endl;
                return;
            }
            else
                r[len].iskongxian = false;
            break;
        }
    }
    if(!flag)
    {
        cout << "您没有该房间可以出租！" << endl;
        return;
    }
    f[i].update = to_string(1900 + ltm->tm_year) +
                  "-" + to_string(1 + ltm->tm_mon) +
                  "-" + to_string(ltm->tm_mday) +
                  "_" + to_string(ltm->tm_hour) +
                  ":" + to_string(ltm->tm_min) +
                  ":" + to_string(ltm->tm_sec);

    cout << endl
         << "预付费用 : ";
    cin >> f[i].yajin;
    ++No_Fangke;

    cout << "房客创建成功！" << endl;
}

void create(Fangke *f, string name, int num)
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int j = No_Fangke;
    string idcard;                                  //用于判断是否有重复的证件号码
    cout << endl
         << "客人身份证号码 : ";
    getline(cin, idcard);
    if (No_Fangke != 0)
    {
        for (int i = 0; i < No_Fangke; ++i)
        {
            if(f[i].idcard==idcard && f[i].name != name)
            {
                cout << "该身份证号码已存在！" << endl;
                return;
            }
            if (f[i].idcard == idcard && f[i].tuidate == "0")
            {
                cout << "该客户以入住:" << f[i].Room_num << "是否还要入住其他房间？(Y/N)" << endl;
                char is;
                cin >> is;
                if(is!='Y')
                    return;
            }
        }
    }
    f[j].idcard = idcard;
    f[j].name = name;
    f[j].Room_num = num;
    f[j].update = to_string(1900 + ltm->tm_year) +
                  "-" + to_string(1 + ltm->tm_mon) +
                  "-" + to_string(ltm->tm_mday) +
                  "_" + to_string(ltm->tm_hour) +
                  ":" + to_string(ltm->tm_min) +
                  ":" + to_string(ltm->tm_sec);
    cout << endl
         << "预付费用 : ";
    cin >> f[j].yajin;
    ++No_Fangke;
    ::room[No_Room].iskongxian = false;
    cout << "房客创建成功！" << endl;

}

void look_fangke(Room *r, Fangke *f)               //查询所有房客
{
    if(No_Fangke==0)
    {
        cout << "您目前还没有房客！" << endl;
        return;
    }

    for (int j = 0; j < No_Fangke;++j)
    {

        cout << "房客信息：" << f[j].name << endl
                << "证件号码：" << f[j].idcard << endl
                << "入住时间：" << f[j].update << endl
                << "预付费用：" << f[j].yajin << endl;
        if (f[j].tuidate != "0")
        {
            cout << "退房时间：" << f[j].tuidate << endl;
            cout << "当时居住房间号：" << f[j].Room_num << endl;
        }
        else
        {
            for (int i = 0; i < No_Room; ++i)
            {
                if(f[j].Room_num == r[i].Room_num)
                {
                    cout << "房间号：" << r[i].Room_num << endl
                         << "房间类型：" << r[i].Room_type << endl
                         << "房间价格：" << r[i].Room_price << endl;
                }
            }
        }
        cout << "---------------------------------------------" << endl;
    }

}
void look_fangke(Room *r, Fangke *f, string idcard)   //根据身份证号码查询房客
{
    bool flag = false;
    for (int j = 0; j < No_Fangke; ++j)
    {
        if(f[j].idcard == idcard)
        {
            flag = true;
            cout << "房客信息：" << f[j].name << endl
                << "证件号码：" << f[j].idcard << endl
                << "入住时间：" << f[j].update << endl
                << "预付费用：" << f[j].yajin << endl;
            if (f[j].tuidate != "0")
            {
                cout << "退房时间：" << f[j].tuidate << endl;
                cout << "当时居住房间号：" << f[j].Room_num << endl;
            }
            else
            {
                for (int i = 0; i < No_Room; ++i)
                {
                    if(f[j].Room_num == r[i].Room_num)
                    {
                        cout << "房间号：" << r[i].Room_num << endl
                            << "房间类型：" << r[i].Room_type << endl
                            << "房间价格：" << r[i].Room_price << endl;
                    }
                }
            }
            cout << "---------------------------------------------" << endl;
        }
    }
    if(!flag)
    {
        cout << "没有找到该房客！" << endl;
    }
}
void look_fangke1(Room *r, Fangke *f, string name)  //根据房客姓名查询房客
{
    bool flag = false;
    for (int j = 0; j < No_Fangke; ++j)
    {
        if(f[j].name == name)
        {
            flag = true;
            cout << "房客信息：" << f[j].name << endl
                << "证件号码：" << f[j].idcard << endl
                << "入住时间：" << f[j].update << endl
                << "预付费用：" << f[j].yajin << endl;
            if (f[j].tuidate != "0")
            {
                cout << "退房时间：" << f[j].tuidate << endl;
                cout << "当时居住房间号：" << f[j].Room_num << endl;
            }
            else
            {
                for (int i = 0; i < No_Room; ++i)
                {
                    if(f[j].Room_num == r[i].Room_num)
                    {
                        cout << "房间号：" << r[i].Room_num << endl
                            << "房间类型：" << r[i].Room_type << endl
                            << "房间价格：" << r[i].Room_price << endl;
                    }
                }
            }
            cout << "---------------------------------------------" << endl;
        }
    }
    if(!flag)
    {
        cout << "没有找到该房客！" << endl;
    }
}

void tuif(Fangke *f, Room *r)
{
    bool r_flag = false;                          //判断房间是否存在
    bool f_flag = false;                          //判断房客是否在住
    time_t now = time(0);
    tm *ltm = localtime(&now);
    cout << "请输入需要退订的房间号：" << endl;
    int num, i = No_Room - 1, j = 0;
    cin >> num;
    for (; j < No_Fangke; ++j)
    {
        if (f[j].Room_num == num && f[j].tuidate == "0")
        {
            f_flag = true;
            break;
        }
    }
    for (; i >= 0; --i)
    {
        if (r[i].Room_num == num)
        {
            r_flag = true;
            look(r, f, num);
            break;
        }
    }
    if(r_flag && f_flag)
    {
        cout << "请确定是否需要退订(Y/N)" << endl;
        char is;
        cin >> is;
        if(is == 'Y')
        {
            r[i].iskongxian = true;
            f[j].tuidate = to_string(1900 + ltm->tm_year) +
                  "-" + to_string(1 + ltm->tm_mon) +
                  "-" + to_string(ltm->tm_mday) +
                  "_" + to_string(ltm->tm_hour) +
                  ":" + to_string(ltm->tm_min) +
                  ":" + to_string(ltm->tm_sec);
            cout << "退订成功！" << endl;
        }
    }
    if(!r_flag)
    {
        cout << "没有找到该房间！" << endl;
    }
}

void update_text(Room *r, Fangke *f)
{
    ofstream room("Room", ios::out);
    for (int i = 0; i < No_Room; ++i)
    {
        room << endl
             << r[i].Room_num << ' ' << r[i].Room_type << ' ' << r[i].Room_price << ' ';
        if (!r[i].iskongxian)
            room << 0;
        else
            room << 1;
    }
    room.close();
    ofstream fangke("fangke", ios::out);
    for (int i = 0; i < No_Fangke; ++i)
    {
        fangke << endl
               << f[i].idcard << ' ' << f[i].name << ' ' << f[i].Room_num << ' ' << f[i].yajin << ' ' << f[i].update << ' '<<f[i].tuidate;
    }
    fangke.close();
}