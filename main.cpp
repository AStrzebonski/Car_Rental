#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;
//klasa przechowujaca date
class Date {
private:
    int day=0;
    int month=0;
    int year=0;
public:
    //konstruktory
    Date(int day_, int month_, int year_)
    {
        day=day_;
        month=month_;
        year=year_;
    }
    Date(){}
    //gettery
    int get_day() {return day;}
    int get_month() {return month;}
    int get_year() {return year;}
    //settery
    void set_day(int day_) {day=day_;}
    void set_month(int month_) {month=month_;}
    void set_year(int year_) {year=year_;}
    //metoda sprawdzajaca poprawnosc daty
    bool check_validity()
    {
        if(month<1 || month>12 || day<1 || day>31 || year<1000 || year>9999)
            return false;
        if(day==31 && (month==4 || month==6 || month==9 || month==11))
            return false;
        if(month==2 && year%4!=0 && day>28)
            return false;
        if(month==2 && year%4==0 && day>29)
            return false;
        return true;
    }
    //metoda wypisujaca date na ekran
    void print()
    {
        cout<<day<<"."<<month<<"."<<year;
    }
    //metoda przeksztalcajaca date na string
    string date_to_string()
    {
        string s="";
        if(day==0)
            return "none";
        if(day<10)
            s+="0";
        s+=to_string(day);
        s+=".";
        if(month<10)
            s+="0";
        s+=to_string(month);
        s+=".";
        s+=to_string(year);
        return s;
    }
};
//przeciazenie operatora przyrownania dla klasy Date
inline bool operator<(Date& lhs, Date& rhs)
{
    if(lhs.get_year()<rhs.get_year())
        return true;
    if(lhs.get_year()>rhs.get_year())
        return false;
    if(lhs.get_month()<rhs.get_month())
        return true;
    if(lhs.get_month()>rhs.get_month())
        return false;
    if(lhs.get_day()<rhs.get_day())
        return true;
    if(lhs.get_day()>rhs.get_day())
        return false;
    return false;
}
//klasa przechowujaca parametry samachodu
class Car {
private:
    string brand;
    string model;
    int prod_year;
    int capacity;
    double price; //price per day
    string reg;
    Date return_date;
public:
    //konstruktory
    Car(string brand_, string model_, int prod_year_, int capacity_, string reg_, double price_, Date return_date_)
    {
        brand=brand_;
        model=model_;
        prod_year=prod_year_;
        capacity=capacity_;
        price=price_;
        reg=reg_;
        return_date=return_date_;
    }
    Car(){}
    //gettery
    string get_brand() {return brand;}
    string get_model() {return model;}
    int get_prod_year() {return prod_year;}
    int get_capacity() {return capacity;}
    double get_price() {return price;}
    string get_reg() {return reg;}
    Date get_return_date() {return return_date;}
    //settery
    void set_brand(string brand_) {brand=brand_;}
    void set_model(string model_) {model=model_;}
    void set_prod_year(int prod_year_) {prod_year=prod_year_;}
    void set_capacity(int capacity_) {capacity=capacity_;}
    void set_price(double price_) {price=price_;}
    void set_reg(string reg_) {reg=reg_;}
    void set_return_date(int day_, int month_, int year_)
    {
        return_date.set_day(day_);
        return_date.set_month(month_);
        return_date.set_year(year_);
    }
    void set_return_date(Date return_date_) {return_date=return_date_;}
    //metoda wypisujaca parametry samochodu na ekran
    void print()
    {
        cout<<brand<<" | "<<model<<" | "<<prod_year<<" | "<<capacity<<" | "<<price<<" | "<<reg<<" | ";
        if(return_date.get_day()==0)
            cout<<"none"<<endl;
        else
            cout<<return_date.get_day()<<"."<<return_date.get_month()<<"."<<return_date.get_year()<<endl;
    }
};
//funkcja wypisujaca wszystkie samochody na ekran
void print_all_records(vector<Car>& cars_)
{
    cout<<"brand|model|prod year|capacity|price per day|register number|return date"<<endl;
    for(size_t i=0;i<cars_.size();i++)
    {
        cars_[i].print();
    }
}
//funkcja wypisujaca dostepne samochody na ekran (te w ktorych return date to 0.0.0)
void print_available_records(vector<Car>& cars_)
{
    cout<<"brand|model|prod year|capacity|price per day|register number|return date"<<endl;
    for(size_t i=0;i<cars_.size();i++)
    {
        if(cars_[i].get_return_date().get_day()==0)
            cars_[i].print();
    }
}
//funkcja ktora wyszukuje wyszukuje samochod po numerze rejestracyjnym i zwraca indeks znalezionego samochodu lub -1 jezeli nic nie znajdzie
int find_record_by_register(vector<Car>& cars_, string reg)
{
    for(size_t i=0;i<cars_.size();i++)
    {
        if(cars_[i].get_reg()==reg)
            return i;
    }
    return -1;
}
//funkcja ktora wykorzystujac terminal przeprowadza komunikacje z uzytkownikiem w celu wypisania na ekran interesujacych go samochodow
void searching(vector<Car>& cars_)
{
    string input;
    string brand="";
    int min_cap=0;
    int max_cap=10000;
    double min_price=0;
    double max_price=1e12;
    bool available;
    while(1)
    {
        min_cap=0;
        max_cap=10000;
        min_price=0;
        max_price=1e12;
        available=false;
        cout<<"Searching menu:"<<endl<<"You can always type 'back' to go back to menu."<<endl<<"Do you want to search for concrete brand? [yes/no]"<<endl;
        getline(cin, input);
        if(input=="back")
            break;
        if(input=="yes")
        {
            cout<<"Type brand name you want to search for"<<endl;
            getline(cin, input);
            if(input=="back")
                break;
            brand=input;
        }
        else if(input!="no")
        {
            cout<<"Unrecognized command."<<endl;
            continue;
        }
        cout<<"Do you want to search for concrete capacity? [yes/no/back]"<<endl;
        getline(cin, input);
        if(input=="back")
            break;
        if(input=="yes")
        {
            cout<<"Type minimal capacity (min. 1) you want to search for or 'none'."<<endl;
            getline(cin, input);
            if(input=="back")
                break;
            if(input=="none"){}
            else if(atoi(input.c_str())<=0 || atoi(input.c_str())>1000)
            {
                cout<<"Invalid capacity."<<endl;
                continue;
            }
            else
                min_cap=atoi(input.c_str());
            cout<<"Type maximal capacity you want to search for or 'none'."<<endl;
            getline(cin, input);
            if(input=="back")
                break;
            if(input=="none"){}
            else if(atoi(input.c_str())==0 || atoi(input.c_str())>1000 || atoi(input.c_str())<min_cap)
            {
                cout<<"Invalid capacity."<<endl;
                continue;
            }
            else
                max_cap=atoi(input.c_str());
        }
        else if(input!="no")
        {
            cout<<"Unrecognized command."<<endl;
            continue;
        }
        cout<<"Do you want to search for concrete price per day? [yes/no/back]"<<endl;
        getline(cin, input);
        if(input=="back")
            break;
        if(input=="yes")
        {
            cout<<"Type minimal price you want to search for or 'none'."<<endl;
            getline(cin, input);
            if(input=="back")
                break;
            if(input=="none"){}
            else
            {
                try
                {
                    if(stod(input.c_str())>=0 && stod(input.c_str())<1e12)
                        min_price=stod(input.c_str());
                    else
                    {
                        cout<<"Invalid price."<<endl;
                        continue;
                    }
                }
                catch(...)
                {
                    cout<<"Invalid price."<<endl;
                    continue;
                }
            }
            cout<<"Type maximal price you want to search for or 'none'."<<endl;
            getline(cin, input);
            if(input=="back")
                break;
            if(input=="none"){}
            else
            {
                try
                {
                    if(stod(input.c_str())<1e12 && stod(input.c_str())>=min_price)
                        max_price=stod(input.c_str());
                    else
                    {
                        cout<<"Invalid price."<<endl;
                        continue;
                    }
                }
                catch(...)
                {
                    cout<<"Invalid price."<<endl;
                    continue;
                }
            }

        }
        else if(input!="no")
        {
            cout<<"Unrecognized command."<<endl;
            continue;
        }
        cout<<"Do you want to search only for available cars? [yes/no/back]"<<endl;
        getline(cin, input);
        if(input=="back")
            break;
        if(input=="yes")
            available=true;
        else if(input!="no")
        {
            cout<<"Unrecognized command."<<endl;
            continue;
        }
        cout<<"brand|model|prod year|capacity|price per day|register number|return date"<<endl;
        for(size_t i=0;i<cars_.size();i++)
        {
            if(cars_[i].get_brand()==brand || brand=="")
            {
                if(cars_[i].get_capacity()>=min_cap && cars_[i].get_capacity()<=max_cap)
                {
                    if(cars_[i].get_price()>=min_price && cars_[i].get_price()<=max_price)
                    {
                        if((available==false) || (cars_[i].get_return_date().get_day()==0))
                            cars_[i].print();
                    }
                }
            }
        }
        break;
    }
}

int main()
{
    string password="admin";
    vector<Car> cars;
    string line;
    int pos1;
    int pos2;
    Car c;
    int day;
    int month;
    int year;
    Date d;
    time_t now = time(0);
    tm *ltm = localtime(&now);
    Date current_date;
    current_date.set_year(1900 + ltm->tm_year);
    current_date.set_month(1 + ltm->tm_mon);
    current_date.set_day(ltm->tm_mday);
    current_date.print();
    cout<<endl;

    fstream file_r ("cars.txt");
    if(file_r.is_open())
    {
        getline(file_r,line); //pierwsza linia to niepotrzebny naglowek
        while(getline(file_r, line))
        {
            pos2=line.find("|", 0);
            c.set_brand(line.substr(0,pos2));
            pos1=pos2+1;
            pos2=line.find("|", pos1);
            c.set_model(line.substr(pos1, pos2-pos1));
            pos1=pos2+1;
            pos2=line.find("|", pos1);
            c.set_prod_year(atoi(line.substr(pos1, pos2-pos1).c_str()));
            pos1=pos2+1;
            pos2=line.find("|", pos1);
            c.set_capacity(atoi(line.substr(pos1,pos2-pos1).c_str()));
            pos1=pos2+1;
            pos2=line.find("|", pos1);
            c.set_price(stod(line.substr(pos1,pos2-pos1).c_str()));
            pos1=pos2+1;
            pos2=line.find("|", pos1);
            c.set_reg(line.substr(pos1, pos2-pos1));
            pos1=pos2+1;
            if(line.substr(pos1)!="none")
            {
                day=atoi(line.substr(pos1,2).c_str());
                month=atoi(line.substr(pos1+3,2).c_str());
                year=atoi(line.substr(pos1+6,4).c_str());
                c.set_return_date(day, month, year);
            }
            else
                c.set_return_date(0,0,0);
            cars.push_back(c);
        }
        file_r.close();
    }
    else
    {
        cout<<"Error during file opening!"<<endl;
        return 0;
    }
    while(1)
    {
        Main_menu:
        cout<<"Main menu:"<<endl<<"Type 'a' to enter admin mode."<<endl<<"Type 'u' to enter user mode."<<endl<<"Type 'exit' to exit."<<endl;
        string input;
        getline(cin, input);
        if(input=="exit")
            break;
        else if(input=="a")
        {
            Entering_password:
            cout<<"Enter password or type 'back' to return to main menu."<<endl;
            getline(cin, input);
            if(input=="back")
            {
                goto Main_menu;
            }
            if(input!=password)
            {
                cout<<"password incorrect!"<<endl;
                goto Entering_password;
            }
            //tryb administratora
            Admin_menu:
            cout<<"Admin menu:"<<endl<<"Type 'back' to return to main menu."<<endl<<"Type 'print' to print all records."<<endl
            <<"Type 'add' to add new record."<<endl<<"Type 'delete' to delete record."<<endl
            <<"Type 'search' to search for some records"<<endl<<"Type 'change' to change record."<<endl;
            getline(cin, input);
            if(input=="back")
                goto Main_menu;
            else if(input=="print")
                print_all_records(cars);
            else if(input=="search")
                searching(cars);
            else if(input=="add")
            {
                cout<<"Type brand or 'quit'."<<endl;
                getline(cin, input);
                if(input=="quit")
                    goto Admin_menu;
                c.set_brand(input);
                cout<<"Type model or 'quit'."<<endl;
                getline(cin, input);
                if(input=="quit")
                    goto Admin_menu;
                c.set_model(input);
                Setting_year:
                cout<<"Type year of production or 'quit'."<<endl;
                getline(cin, input);
                if(input=="quit")
                    goto Admin_menu;
                if(atoi(input.c_str())!=0)
                    c.set_prod_year(atoi(input.c_str()));
                else
                {
                    cout<<"Invalid year."<<endl;
                    goto Setting_year;
                }
                Setting_capacity:
                cout<<"Type capacity or 'quit'."<<endl;
                getline(cin, input);
                if(input=="quit")
                    goto Admin_menu;
                if(atoi(input.c_str())!=0)
                    c.set_capacity(atoi(input.c_str()));
                else
                {
                    cout<<"Invalid capacity."<<endl;
                    goto Setting_capacity;
                }
                Setting_price:
                cout<<"Type price per day or 'quit'."<<endl;
                getline(cin, input);
                if(input=="quit")
                    goto Admin_menu;
                try{c.set_price(stod(input));}
                catch(...){
                    cout<<"Invalid price!"<<endl;
                    goto Setting_price;}
                cout<<"Type register number or 'quit'."<<endl;
                getline(cin, input);
                if(input=="quit")
                    goto Admin_menu;
                c.set_reg(input);
                Setting_return_date:
                cout<<"Type day of return date or 'none' or 'quit'."<<endl;
                getline(cin, input);
                if(input=="quit")
                    goto Admin_menu;
                if(input!="none")
                {
                    d.set_day(atoi(input.c_str()));
                    cout<<"Type month of return date or 'quit'."<<endl;
                    getline(cin, input);
                    if(input=="quit")
                        goto Admin_menu;
                    d.set_month(atoi(input.c_str()));
                    cout<<"Type year of return date or 'quit'."<<endl;
                    getline(cin, input);
                    if(input=="quit")
                        goto Admin_menu;
                    d.set_year(atoi(input.c_str()));
                    if(!d.check_validity())
                    {
                        cout<<"Invalid date!"<<endl;
                        goto Setting_return_date;
                    }
                    c.set_return_date(d);
                }
                else
                    c.set_return_date(0,0,0);
                cars.push_back(c);
                cout<<"Record added successfully."<<endl;
            }
            else if(input=="delete")
            {
                Deleting_record:
                cout<<"Type register number or 'quit'."<<endl;
                getline(cin, input);
                if(input=="quit")
                    goto Admin_menu;
                int iter=find_record_by_register(cars, input);
                if(iter==-1)
                    {
                        cout<<"Record not found!"<<endl;
                        goto Deleting_record;
                    }
                cars.erase(cars.begin()+iter);
                cout<<"Record deleted successfully!"<<endl;
            }
            else if(input=="change")
            {
                Changing_record:
                cout<<"Type register number or 'quit'."<<endl;
                getline(cin, input);
                if(input=="quit")
                    goto Admin_menu;
                int iter=find_record_by_register(cars, input);
                if(iter==-1)
                    {
                        cout<<"Record not found!"<<endl;
                        goto Changing_record;
                    }
                cout<<"Type new register number or 'keep' or 'quit'."<<endl;
                getline(cin, input);
                if(input=="quit")
                    goto Admin_menu;
                if(input!="keep")
                {
                    cars[iter].set_reg(input);
                }
                Changing_price:
                cout<<"Type new price or 'keep' or 'quit'."<<endl;
                getline(cin, input);
                if(input=="quit")
                    goto Admin_menu;
                if(!(input=="keep"))
                {
                    try{cars[iter].set_price(stod(input));}
                    catch(...){
                        cout<<"Invalid price"<<endl;
                        goto Changing_price;}
                }
                Changing_return_date:
                cout<<"Type new day of return date or 'none' or 'keep' to keep current return date or 'quit'."<<endl;
                getline(cin, input);
                if(input=="quit")
                    goto Admin_menu;
                if(input=="keep"){}
                else if(input!="none")
                {
                    d.set_day(atoi(input.c_str()));
                    cout<<"Type month of return date or 'quit'."<<endl;
                    getline(cin, input);
                    if(input=="quit")
                        goto Admin_menu;
                    d.set_month(atoi(input.c_str()));
                    cout<<"Type year of return date or 'quit'."<<endl;
                    getline(cin, input);
                    if(input=="quit")
                        goto Admin_menu;
                    d.set_year(atoi(input.c_str()));
                    if(!d.check_validity())
                    {
                        cout<<"Invalid date!"<<endl;
                        goto Changing_return_date;
                    }
                    cars[iter].set_return_date(d);
                }
                else
                    cars[iter].set_return_date(0,0,0);
            }
            else
                cout<<"Unrecognized command!"<<endl;
            goto Admin_menu;
        }
        else if(input=="u")
        {
            User_menu:
            cout<<"User menu:"<<endl<<"Type 'back' to return to main menu."<<endl<<"Type 'print' to print all cars."<<endl
            <<"Type 'book' to book new record."<<endl
            <<"Type 'search' to search for some records."<<endl<<"Type 'print_av' to print available cars."<<endl;
            getline(cin, input);
            if(input=="back")
                goto Main_menu;
            else if(input=="print")
                print_all_records(cars);
            else if(input=="print_av")
                print_available_records(cars);
            else if(input=="search")
                searching(cars);
            else if(input=="book")
            {
                Booking:
                cout<<"Booking menu:"<<endl<<"Type register number or 'quit'."<<endl;
                getline(cin, input);
                if(input=="quit")
                    goto User_menu;
                int iter=find_record_by_register(cars, input);
                if(iter==-1)
                {
                    cout<<"No such car!"<<endl;
                    goto Booking;
                }
                if(cars[iter].get_return_date().get_day()!=0)
                {
                    cout<<"This car is not available! It is rented until ";
                    cars[iter].get_return_date().print();
                    cout<<"."<<endl;
                    goto Booking;
                }
                Booking_return_date:
                cout<<"Type day of return date or 'quit'."<<endl;
                getline(cin, input);
                if(input=="quit")
                    goto User_menu;
                d.set_day(atoi(input.c_str()));
                cout<<"Type month of return date or 'quit'."<<endl;
                getline(cin, input);
                if(input=="quit")
                    goto User_menu;
                d.set_month(atoi(input.c_str()));
                cout<<"Type year of return date or 'quit'."<<endl;
                getline(cin, input);
                if(input=="quit")
                    goto User_menu;
                d.set_year(atoi(input.c_str()));
                if(!d.check_validity())
                {
                    cout<<"Invalid date!"<<endl;
                    goto Booking_return_date;
                }
                if(d<current_date)
                {
                    cout<<"Chosen return date is before today!"<<endl;
                    goto Booking;
                }
                cars[iter].set_return_date(d);
                cout<<"Car booked successfully!"<<endl;
            }
            else
                cout<<"Unrecognized command!"<<endl;
            goto User_menu;
        }
        else
        {
            cout<<"Unrecognized command!"<<endl;
            continue;
        }
    }
    //Writing cars to file
    fstream file_w ("cars.txt");
    if(file_w.is_open())
    {
        file_w<<"brand|model|prod_year|capacity|price per day|register number|return date[dd.mm.yyyy]"<<endl;
        for(size_t i=0;i<cars.size();i++)
        {
            file_w<<cars[i].get_brand()<<"|"<<cars[i].get_model()<<"|"<<cars[i].get_prod_year()<<"|"<<cars[i].get_capacity()<<"|"
            <<cars[i].get_price()<<"|"<<cars[i].get_reg()<<"|";
            file_w<<cars[i].get_return_date().date_to_string();
            if(i<(cars.size()-1))
                file_w<<endl;
        }
        file_w.close();
        cout<<"Changes saved successfully!"<<endl;
    }
    else
    {
        cout<<"Couldn't open file to write! Changes will not be saved!"<<endl;
        return 0;
    }
}
