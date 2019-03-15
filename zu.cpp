/*
 *���ݵĿͷ���Ϣ�����ͷ��š��ͷ����͡��ͷ��۸񡢿�������������������������֤�š���סʱ�䡢�˷�ʱ�䣬Ԥ�����õ���Ϣ��
 *�����һ���ݿͷ�����ϵͳͳ��ϵͳ�Բ˵���ʽ������ʹ֮���ṩ���¹��ܣ�
 *�ͷ���Ϣ��¼�빦��
 *������ס�Ǽ�
 *�����˷�����
 *�ͷ���Ϣ������ܣ����ȫ���ͷ�����Ϣ
 *�ͷ���Ϣ��ѯ����ѯ�շ���������������򷿼�Ų�ѯ
 *�ͷ���Ϣ��ɾ�����޸Ĺ���
 *���ش洢����ͷ�����Ϣ
 */

#include <iostream>
#include <ctime>
#include <cstdio>
#include<fstream>
using namespace std;

static int No_Room = 0;                             //����id������ͳ�Ʒ�������
static int No_Fangke = 0;                           //����ͳ�Ʒ�������
struct Room
{
    int Room_num;                                   //�����
    string Room_type;                               //��������
    double Room_price;                              //����۸�
    bool iskongxian = true;                         //�Ƿ����
    string name = "";                               //��������
} *room = new Room[20];

struct Fangke
{
    string name;                                    //��������
    string idcard;                                  //�������֤����
    int Room_num = 0;                               //��ס�����
    string update;                                  //��סʱ��
    string tuidate = "0";                            //�˷�ʱ��
    double yajin;                                   //Ԥ������

} *fangke = new Fangke[50];



void create(Room *r);                               //��������
void delroom(Room *r);                              //ɾ������
void look(Room *r, Fangke *f);                      //�鿴���з���
void look(Room *r, Fangke *f, int num);             //���ݷ���Ų鿴�÷���
void look(Room *r, Fangke *f, string name);         //���ݷ�����Ϣ���ҷ���

void create(Fangke *f, Room *r);                    //��������
void create(Fangke *f, string name, int num);       //�Ӵ��������Ǵ�������
void look_fangke(Room *r, Fangke *f);               //��ѯ���з���
void look_fangke(Room *r, Fangke *f, string idcard); //����֤�������ѯ����
void look_fangke1(Room *r, Fangke *f, string name);  //���ݷ���������ѯ����
void tuif(Fangke *f, Room *r);                      //�˷�

void update_text(Room *r, Fangke *f);                //����д������
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
        cout << "1����������\n"
         << "2��ɾ������\n"
         << "3���鿴����\n"
         << "4���Ǽ���ס\n"
         << "5���˷�\n"
         << "6����ѯ����\n"
         << "q���˳�ϵͳ\n";
        cin >> shuru;
        system("cls");
        string test;
        getline(cin, test);
        switch(shuru)
        {
            case '1':                           //��������
                cout << "-----------��������---------" << endl;
                create(room);
                break;
            case '2':                           //ɾ������
            {
                cout << "-----------ɾ������---------" << endl;
                delroom(room);
                break;
            }
            case '3':                           //�鿴����
            {
                cout << "-----------�鿴����---------" << endl;
                cout << "1���鿴���з���\n"
                    << "2�����ݷ���Ų鿴�÷���\n";
                char look_type;
                cin >> look_type;
                switch(look_type)
                {
                    case '1':
                        look(room, fangke);
                        break;
                    case '2':
                    {
                        cout << "�����뷿���:";
                        int num;
                        cin >> num;
                        look(room, fangke, num);
                        break;
                    }
                    default:
                        cout << "�������" << endl;
                }
                break;
            }
            case '4':                           //�Ǽ���ס
                cout << "-----------�Ǽ���ס---------" << endl;
                create(fangke,room);
                break;
            case '5':                           //�˷�
                cout << "-----------�˷�---------" << endl;
                tuif(fangke,room);
                break;
            case '6':
            {
                cout << "-----------��ѯ����---------" << endl;
                cout << "1����ѯ���з���\n"
                     << "2�����ݷ���������ѯ����\n"
                     << "3���������֤�����ѯ����\n";
                char look_type;
                cin >> look_type;
                switch(look_type)
                {
                    case '1':
                        look_fangke(room, fangke);
                        break;
                    case '2':
                    {
                        cout << "������ͻ�����:";
                        string name;
                        cin >> name;
                        look_fangke1(room, fangke, name);
                        break;
                    }
                    case '3':
                    {
                        cout << "���������֤����:";
                        string idcard;
                        cin.get();
                        getline(cin, idcard);
                        look_fangke(room, fangke, idcard);
                        break;
                    }
                    default:
                        cout << "�������" << endl;
                }
                break;
            }

            case 'q':                           //�˳�ϵͳ
                update_text(room, fangke);
                break;
            default:
                cout << "�������" << endl;
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
    cout << "����� : ";
    cin >> num;
    for (int len = 0; len < No_Room; ++len)
    {
        if(r[len].Room_num==num)
        {
            cout << "�Ѵ��ڸ÷���" << endl;
            return;
        }
    }
    r[i].Room_num = num;
    cout << endl
         << "�������� : ";
    cin >> r[i].Room_type;
    cout << endl
         << "����۸� : ";
    cin >> r[i].Room_price;
    cout << endl
         << "�Ƿ�Ϊ���з���(Y/N)��";
    char is;
    cin >> is;
    if (is != 'Y')
    {
        cout << endl
             << "�����뷿������ :";
        cin.get();
        getline(cin, r[i].name);
        create(fangke, r[i].name, r[i].Room_num);
    }

    ++No_Room;
    cout << "���䴴���ɹ���" << endl;
}

void delroom(Room *r)
{
    cout << "��������Ҫɾ���ķ���� : ";
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
                cout << "��Ҫɾ���ķ��䲻Ϊ����״̬���޷�ɾ����" << endl;
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
                cout << "ɾ���ɹ���" << endl;
                break;
            }
        }
    }
    if(!flag)
        cout << "û���ҵ��÷��䣡" << endl;
}

void look(Room *r, Fangke *f)
{
    if (No_Room == 0)
    {
        cout << "��Ŀǰû�п��Գ���ķ���" << endl;
        return;
    }
    for (int i = 0; i < No_Room; ++i)
    {
        cout << "����ţ�" << r[i].Room_num << endl
             << "�������ͣ�" << r[i].Room_type << endl
             << "����۸�" << r[i].Room_price << endl;
        if(!r[i].iskongxian)
        {
            for (int j = No_Fangke - 1; j >= 0; --j)
            {
                if(r[i].Room_num == f[j].Room_num)
                {
                    cout << "������Ϣ��" << f[j].name << endl
                            << "֤�����룺" << f[j].idcard << endl
                            << "��סʱ�䣺" << f[j].update << endl
                            << "Ԥ�����ã�" << f[j].yajin << endl;
                    break;
                }
            }
        }
        else
            cout << "�շ��䣬���޷��;�ס��" << endl;
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
            cout << "����ţ�" << r[i].Room_num << endl
                 << "�������ͣ�" << r[i].Room_type << endl
                 << "����۸�" << r[i].Room_price << endl;
            if(!r[i].iskongxian)
            {
                for (int j = No_Fangke - 1; j >= 0; --j)
                {
                    if(r[i].Room_num == f[j].Room_num)
                    {
                        cout << "������Ϣ��" << f[j].name << endl
                                << "֤�����룺" << f[j].idcard << endl
                                << "��סʱ�䣺" << f[j].update << endl
                                << "Ԥ�����ã�" << f[j].yajin << endl;
                        break;
                    }
                }
            }
            else
                cout << "�շ��䣬���޷��;�ס��" << endl;
            cout << "---------------------------------------------" << endl;
        }
    }
    if(!flag)
        cout << "û���ҵ��÷��䣡" << endl;
}

void look(Room *r, Fangke *f, string name)
{
    bool flag = false;
    for (int i = 0; i < No_Room;++i)
    {
        if(r[i].name == name)
        {
            flag = true;
            cout << "����ţ�" << r[i].Room_num << endl
                 << "�������ͣ�" << r[i].Room_type << endl
                 << "����۸�" << r[i].Room_price << endl;
                for (int j = 0; j < No_Fangke;++j)
                {
                    if(r[i].Room_num == f[j].Room_num)
                    {
                        cout << "������Ϣ��" << f[j].name << endl
                                << "֤�����룺" << f[j].idcard << endl
                                << "��סʱ�䣺" << f[j].update << endl
                                << "Ԥ�����ã�" << f[j].yajin << endl;
                    }
                }
            cout << "---------------------------------------------" << endl;
            break;
        }
    }
    if(!flag)
        cout << "�÷���û����ס��" << endl;
}

void create(Fangke *f, Room *r)
{
    int i = No_Fangke;
    bool flag = false;
    string idcard;
    time_t now = time(0);
    tm *ltm = localtime(&now);
    cout << "�������� : ";

    getline(cin, f[i].name);
    cout << endl
         << "�������֤���� : ";
    getline(cin, idcard);
    if (No_Fangke != 0)
    {
        for (int j = 0; j < No_Fangke; ++j)
        {
            if(f[j].idcard==idcard && f[j].name != f[i].name)
            {
                cout << "�����֤�����Ѵ��ڣ�";
                return;
            }
            if (f[j].idcard == idcard && f[j].tuidate == "0")
            {
                cout << "�ÿͻ�����ס:" << f[j].Room_num << "�Ƿ�Ҫ��ס�������䣿(Y/N)" << endl;
                char is;
                cin >> is;
                if(is!='Y')
                    return;
            }
        }
    }
    f[i].idcard = idcard;
    cout << endl
         << "��ס����� : ";
    cin >> f[i].Room_num;
    for (int len = 0; len < No_Room; ++len)
    {
        if (f[i].Room_num == r[len].Room_num)
        {
            flag = true;
            if(!r[len].iskongxian)
            {
                cout << "�÷��䲻�ǿ��з���!" << endl;
                cout << "����ʧ�ܣ�" << endl;
                return;
            }
            else
                r[len].iskongxian = false;
            break;
        }
    }
    if(!flag)
    {
        cout << "��û�и÷�����Գ��⣡" << endl;
        return;
    }
    f[i].update = to_string(1900 + ltm->tm_year) +
                  "-" + to_string(1 + ltm->tm_mon) +
                  "-" + to_string(ltm->tm_mday) +
                  "_" + to_string(ltm->tm_hour) +
                  ":" + to_string(ltm->tm_min) +
                  ":" + to_string(ltm->tm_sec);

    cout << endl
         << "Ԥ������ : ";
    cin >> f[i].yajin;
    ++No_Fangke;

    cout << "���ʹ����ɹ���" << endl;
}

void create(Fangke *f, string name, int num)
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int j = No_Fangke;
    string idcard;                                  //�����ж��Ƿ����ظ���֤������
    cout << endl
         << "�������֤���� : ";
    getline(cin, idcard);
    if (No_Fangke != 0)
    {
        for (int i = 0; i < No_Fangke; ++i)
        {
            if(f[i].idcard==idcard && f[i].name != name)
            {
                cout << "�����֤�����Ѵ��ڣ�" << endl;
                return;
            }
            if (f[i].idcard == idcard && f[i].tuidate == "0")
            {
                cout << "�ÿͻ�����ס:" << f[i].Room_num << "�Ƿ�Ҫ��ס�������䣿(Y/N)" << endl;
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
         << "Ԥ������ : ";
    cin >> f[j].yajin;
    ++No_Fangke;
    ::room[No_Room].iskongxian = false;
    cout << "���ʹ����ɹ���" << endl;

}

void look_fangke(Room *r, Fangke *f)               //��ѯ���з���
{
    if(No_Fangke==0)
    {
        cout << "��Ŀǰ��û�з��ͣ�" << endl;
        return;
    }

    for (int j = 0; j < No_Fangke;++j)
    {

        cout << "������Ϣ��" << f[j].name << endl
                << "֤�����룺" << f[j].idcard << endl
                << "��סʱ�䣺" << f[j].update << endl
                << "Ԥ�����ã�" << f[j].yajin << endl;
        if (f[j].tuidate != "0")
        {
            cout << "�˷�ʱ�䣺" << f[j].tuidate << endl;
            cout << "��ʱ��ס����ţ�" << f[j].Room_num << endl;
        }
        else
        {
            for (int i = 0; i < No_Room; ++i)
            {
                if(f[j].Room_num == r[i].Room_num)
                {
                    cout << "����ţ�" << r[i].Room_num << endl
                         << "�������ͣ�" << r[i].Room_type << endl
                         << "����۸�" << r[i].Room_price << endl;
                }
            }
        }
        cout << "---------------------------------------------" << endl;
    }

}
void look_fangke(Room *r, Fangke *f, string idcard)   //�������֤�����ѯ����
{
    bool flag = false;
    for (int j = 0; j < No_Fangke; ++j)
    {
        if(f[j].idcard == idcard)
        {
            flag = true;
            cout << "������Ϣ��" << f[j].name << endl
                << "֤�����룺" << f[j].idcard << endl
                << "��סʱ�䣺" << f[j].update << endl
                << "Ԥ�����ã�" << f[j].yajin << endl;
            if (f[j].tuidate != "0")
            {
                cout << "�˷�ʱ�䣺" << f[j].tuidate << endl;
                cout << "��ʱ��ס����ţ�" << f[j].Room_num << endl;
            }
            else
            {
                for (int i = 0; i < No_Room; ++i)
                {
                    if(f[j].Room_num == r[i].Room_num)
                    {
                        cout << "����ţ�" << r[i].Room_num << endl
                            << "�������ͣ�" << r[i].Room_type << endl
                            << "����۸�" << r[i].Room_price << endl;
                    }
                }
            }
            cout << "---------------------------------------------" << endl;
        }
    }
    if(!flag)
    {
        cout << "û���ҵ��÷��ͣ�" << endl;
    }
}
void look_fangke1(Room *r, Fangke *f, string name)  //���ݷ���������ѯ����
{
    bool flag = false;
    for (int j = 0; j < No_Fangke; ++j)
    {
        if(f[j].name == name)
        {
            flag = true;
            cout << "������Ϣ��" << f[j].name << endl
                << "֤�����룺" << f[j].idcard << endl
                << "��סʱ�䣺" << f[j].update << endl
                << "Ԥ�����ã�" << f[j].yajin << endl;
            if (f[j].tuidate != "0")
            {
                cout << "�˷�ʱ�䣺" << f[j].tuidate << endl;
                cout << "��ʱ��ס����ţ�" << f[j].Room_num << endl;
            }
            else
            {
                for (int i = 0; i < No_Room; ++i)
                {
                    if(f[j].Room_num == r[i].Room_num)
                    {
                        cout << "����ţ�" << r[i].Room_num << endl
                            << "�������ͣ�" << r[i].Room_type << endl
                            << "����۸�" << r[i].Room_price << endl;
                    }
                }
            }
            cout << "---------------------------------------------" << endl;
        }
    }
    if(!flag)
    {
        cout << "û���ҵ��÷��ͣ�" << endl;
    }
}

void tuif(Fangke *f, Room *r)
{
    bool r_flag = false;                          //�жϷ����Ƿ����
    bool f_flag = false;                          //�жϷ����Ƿ���ס
    time_t now = time(0);
    tm *ltm = localtime(&now);
    cout << "��������Ҫ�˶��ķ���ţ�" << endl;
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
        cout << "��ȷ���Ƿ���Ҫ�˶�(Y/N)" << endl;
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
            cout << "�˶��ɹ���" << endl;
        }
    }
    if(!r_flag)
    {
        cout << "û���ҵ��÷��䣡" << endl;
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