#include <iostream>
#include <string>
#include <vector>


using namespace std;

int user_is_auth = 0;
int id_of_user = -1;
int number_of_payment_orders = 0;


class User {
    string first_name, last_name, username, password;

    string Encrypt(string password, int len);

    string Decrypt(string password, int len);

public:
    User(string first_name, string last_name, string username, string password) {
        this->first_name = first_name;
        this->last_name = last_name;
        this->username = username;
        this->password = Encrypt(password, password.size());

    }

    void print_user() {
        cout << "------- Welcome " << this->username << "! -----------------" << endl;
        cout << "First name:" << this->first_name << endl;
        cout << "Last name:" << this->last_name << endl;
        cout << "Username:" << this->username << endl;
        cout << "Encrypted password:" << this->password << endl;
        cout << "Decrypted password:" << Decrypt(this->password, this->password.size()) << endl;
        cout << "------- This data are confidential -----------------" << endl;
        cout << endl;

    }

    string get_username() {
        return this->username;
    }


    int validate_account(string username, string password);

};


string User::Encrypt(string password, int len) {

    string password_encrypted = password;
    for (int i = 0; (i < 100 && password_encrypted[i] != '\0'); i++) {
        password_encrypted[i] = password_encrypted[i] + len;
    }
    return password_encrypted;

}

string User::Decrypt(string password, int len) {

    string password_decrypt = password;
    for (int i = 0; (i < 100 && password_decrypt[i] != '\0'); i++) {
        password_decrypt[i] = password_decrypt[i] - len;
    }
    return password_decrypt;

}

int User::validate_account(string username, string password) {
    if (this->username == username) {
        if (this->password == Encrypt(password, password.size())) {
            return 1;
        }
        return 0;
    }
    return 0;


}

int check_username(vector<User> users, string username) {
    for (int i = 0; i < users.size(); i++) {
        if (users[i].get_username() == username) {
            return 0;
        }
    }
    return 1;
}

void create_user(vector<User> users) {
    string first_name, last_name, username, password1, password2;
    cout << "Enter first name:";
    cin >> first_name;
    cout << "Enter last name:";
    cin >> last_name;

    do {
        cout << "Enter an username:";
        cin >> username;

    } while (check_username(users, username) != 1);

    do {
        cout << "Enter an password:";
        cin >> password1;
        cout << "Retype an password:";
        cin >> password2;
    } while (password1 != password2);


}


int login(vector<User> users_of_bank, int users_size) {
    string username, password;
    int valid = 0;
    cout << "Please enter your username:";
    cin >> username;
    cout << "Please enter your password:";
    cin >> password;
    for (int i = 0; i < users_size; i++) {
        valid = users_of_bank[i].validate_account(username, password);
        if (valid) {
            user_is_auth = 1;
            return i;
        }
    }
    return -1;
}

class Payment {
    int payment_id;
    int user_id;
    string date;
    string message;
    double value;
public:

    Payment(int user_id, string date, string message, double value) {
        this->payment_id = rand();
        this->user_id = user_id;
        this->date = date;
        this->message = message;
        this->value = value;

        number_of_payment_orders += 1;
    }

    void payment_info(vector<User> users) {
        cout << "------- This data are confidential -----------------" << endl;
        cout << "Payment ID: " << this->payment_id << endl;
        cout << "User ID: " << this->user_id << endl;
        cout << "Username: " << users[user_id].get_username() << endl;
        cout << "Payment date: " << this->date << endl;
        cout << "Payment Message: " << this->message << endl;
        cout << "Payment value: " << this->value << endl;
        cout << "----------------------------------------------------" << endl;
        cout << endl;
    }

    void get_oredr_info(int _user_ID) {
        cout << "------- Payment order details -----------------" << endl;
        cout << "Payment ID: " << this->payment_id << endl;
        cout << "Payment date: " << this->date << endl;
        cout << "Payment Message: " << this->message << endl;
        cout << "Payment value: " << this->value << endl;
        cout << "------- This data are confidential -----------------" << endl;
        cout << endl;
    }

    int get_user_ID() {
        return this->user_id;
    }

    string get_date() {
        return this->date;
    }

    int get_value() {
        return this->value;
    }

};

vector<Payment> user_payment;

void print_payments(vector<Payment> payments, vector<User> users) {

    for (int i = 0; i < payments.size(); i++) {
        payments[i].payment_info(users);
    }
}

void print_payments_of_user(vector<Payment> payments, int user_ID) {
    for (int i = 0; i < payments.size(); i++) {
        if (payments[i].get_user_ID() == user_ID) {
            payments[i].get_oredr_info(user_ID);
        }
    }
}

void get_user_payment(vector<Payment> payments, int user_ID) {
    for (int i = 0; i < payments.size(); i++) {
        if (payments[i].get_user_ID() == user_ID) {
            user_payment.push_back(payments[i]);
        }

    }
}

void sort_from_first_to_last(vector<Payment> payments) {
    for (int i = 0; i < payments.size(); i++) {
        for (int j = 0; j < payments.size(); j++) {
            if (payments[j].get_date() > payments[i].get_date()) {
                vector<Payment> aux;
                aux.push_back(payments[i]);
                payments[i] = payments[j];
                payments[j] = aux[0];


            }
        }
    }
    print_payments_of_user(payments, id_of_user);
}

void sort_from_last_to_first(vector<Payment> payments) {
    for (int i = 0; i < payments.size(); i++) {
        for (int j = 0; j < payments.size(); j++) {
            if (payments[j].get_date() < payments[i].get_date()) {
                vector<Payment> aux;
                aux.push_back(payments[i]);
                payments[i] = payments[j];
                payments[j] = aux[0];


            }
        }
    }
    print_payments_of_user(payments, id_of_user);
}

void sort_ascending(vector<Payment> payments) {
    for (int i = 0; i < payments.size(); i++) {
        for (int j = 0; j < payments.size(); j++) {
            if (payments[j].get_value() > payments[i].get_value()) {
                vector<Payment> aux;
                aux.push_back(payments[i]);
                payments[i] = payments[j];
                payments[j] = aux[0];


            }
        }
    }
    print_payments_of_user(payments, id_of_user);
}

void sort_descending(vector<Payment> payments) {
    for (int i = 0; i < payments.size(); i++) {
        for (int j = 0; j < payments.size(); j++) {
            if (payments[j].get_value() < payments[i].get_value()) {
                vector<Payment> aux;
                aux.push_back(payments[i]);
                payments[i] = payments[j];
                payments[j] = aux[0];


            }
        }
    }
    print_payments_of_user(payments, id_of_user);
}


void login_or_register(vector<User> users) {
    int choice;
    int sw = 0;
    do {


        cout << endl
             << " 1 - Login in Emanuel Bank Internet Banking.\n"
             << " 2 - Create an account.\n"
             << " 3 - Exit.\n"
             << "Type here your choice:";
        cin >> choice;

        switch (choice) {
            case 1:


                do {
                    sw = login(users, users.size());
                } while (sw == -1);
                cout << "Welcome " << users[sw].get_username() << "!\n";
                id_of_user = sw;
                choice = 3;


                break;
            case 2:
                create_user(users);
                cout << "Welcome !\n";
                break;
            default:
                cout << "Not a Valid Choice. \n"
                     << "Choose again.\n";
                break;
        }

    } while (choice != 3);
}

void create_an_payment(vector<Payment> &payments){
    string date,message;
    double value;
    cout<<"Enter the date YYYY-MM-DD:";cin>>date;
    cout<<"Enter the value:";cin>>value;
    cout<<"Enter your message:";cin>>message;
    payments.push_back((Payment(id_of_user,date,message,value)));


}

void payments_menu(vector<User> users, vector<Payment> payments) {

    int choice, choice_payment, choice_create;
    int sw = 0;
    do {


        cout << endl
             << " 1 - See your payment.\n"
             << " 2 - Create an payment.\n"
             << " 3 - Exit.\n"
             << "Type here your choice:";
        cin >> choice;

        switch (choice) {
            case 1:
                do {


                    cout << endl
                         << " 1 - See your payment from first to last.\n"
                         << " 2 - See your payment from last to first.\n"
                         << " 3 - See your payment orders by value in ascending order.\n"
                         << " 4 - See your payment orders by value in decreasing order.\n"
                         << " 5 - Exit.\n"
                         << "Type here your choice:";
                    cin >> choice_payment;

                    switch (choice_payment) {
                        case 1:
                            get_user_payment(payments, id_of_user);

                            sort_from_first_to_last(user_payment);
                            user_payment.clear();


                            break;
                        case 2:
                            get_user_payment(payments, id_of_user);

                            sort_from_last_to_first(user_payment);
                            user_payment.clear();

                            break;
                        case 3:
                            get_user_payment(payments, id_of_user);

                            sort_ascending(user_payment);
                            user_payment.clear();

                            break;
                        case 4:
                            get_user_payment(payments, id_of_user);

                            sort_descending(user_payment);
                            user_payment.clear();

                            break;
                        default:
                            cout << "Not a Valid Choice. \n"
                                 << "Choose again.\n";
                            break;
                    }

                } while (choice_payment != 5);


                break;
            case 2:
                create_an_payment(payments);

                break;
            default:
                cout << "Not a Valid Choice. \n"
                     << "Choose again.\n";
                break;
        }

    } while (choice != 3);


}


int main() {

    vector<User> users;
    users.push_back(User("Emanuel", "Covaci", "emanuelcovaci", "iLovePS#2018"));
    users.push_back(User("Ionel", "UVT", "ioneluvt", "iLoveCocaCola"));
    users.push_back(User("Gica", "UPT", "gicaupt", "iLovePS#2018"));

    vector<Payment> payments_orders;
    payments_orders.push_back(Payment(0, "2018-07-01", "iPhone X", 999.0));
    payments_orders.push_back(Payment(0, "2019-06-01", "Coca Cola x 100 buc", 1530.00));
    payments_orders.push_back(Payment(0, "2018-04-01", "Herbalife Breakfast", 25.0));

    payments_orders.push_back(Payment(1, "2014-07-01", "iPhone", 9399.0));
    payments_orders.push_back(Payment(1, "2012-06-01", "Coca Cola x 1500 buc", 150.00));
    payments_orders.push_back(Payment(1, "2011-04-01", "Herbalife Breakfast", 25.0));

    payments_orders.push_back(Payment(2, "2017-07-01", "iPhone X", 999.0));
    payments_orders.push_back(Payment(2, "2019-06-01", "Coca Cola x 10550 buc", 1350.00));
    payments_orders.push_back(Payment(2, "2012-04-01", "Herbalife Breakfast", 25.0));


    login_or_register(users);
    if (user_is_auth) {
        payments_menu(users, payments_orders);
    }


}