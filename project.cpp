// writing on a text file
#include <iostream>
#include <ctime>
#include <fstream>
using namespace std;


string encryptDecrypt(string toEncrypt) {						//encryption,decryption function
    char key = 'K'; //Any char will work
    string output = toEncrypt;

    for (int i = 0; i < toEncrypt.size(); i++)
        output[i] = toEncrypt[i] ^ key;

    return output;
}
int main () {
  int mode;cout<<"Enter 1 to add new entry, 0 to see the diary\n"; cin>>mode;
  ofstream f ("yourDiary.txt",ios::app);
  time_t now=time(0);
  char *ltm=ctime(&now);
  string line,line2,pwd;
  string encrypted = encryptDecrypt(ltm);						//timestamp encrypted and added to file
  string decrypted;
  f<<encryptDecrypt("**");								//to find end of file
  f<<"\n\n\n\n";
  f << encrypted << "\n\n";
  if(mode==1){
    cout<<"speak your heart out. when you feel better enter **++**\n";
    for(;;){
        getline(cin,line);
        if(line=="**++**"){
            encrypted=encryptDecrypt(line);
            f << encrypted <<"\n";
            break;									//end cuurrent data entry
        }
        else{
            encrypted=encryptDecrypt(line);
            f << encrypted <<"\n";							//line to file
        }
    }
    f.close();
  }
  if (mode==0){
    cout<<"enter password\n";
    cin.ignore();
    getline(cin,pwd);
    if(pwd=="pwd"){									//encryption of password
        ofstream dia("yourDiaryDecrypted.txt",ios::trunc);
        fstream f("yourDiary.txt");
      NEXT: getline(f,line);
        decrypted=encryptDecrypt(line);
        if (decrypted!="**++**"){
            dia<<decrypted<<"\n";
            goto NEXT;									//restart loop
        }
        else{
            getline(f,line2);
            decrypted=encryptDecrypt(line2);
            if(decrypted=="**"){
                dia<<decrypted<<"\n";
                goto NEXT;								//restart loop
            }
            else{
                goto EXIT;								//break loop
            }
        }
      EXIT: dia.close();f.close();
        cout<<"You can now see your decrypted diary\n  :)\n";
    }
    else{
        cout<<"wait for the password. I will give it to you in due time\n";
    }
  }
  cout<<"press enter to continue";
  cin.ignore();
  return 0;
}
