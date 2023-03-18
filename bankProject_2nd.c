//#include <inttypes.h>
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#define USIZE 100

struct transaction{
    char note_1[100];
    unsigned int rcAmount;
    char note_2[100];
    char note_3[100];
};
struct root{
    char rPassword[13];
};

struct database{
    unsigned int id;
    char name[50];
    char email[50];
    char password[50];
    unsigned int phNumber;
    char address[100];
    unsigned int amount;
    char ban[10];
    char note[100];
    struct transaction transRC[100];
    struct root RPass;
};
struct database db[USIZE];
//struct database loginEmail[1];

int gIndex=0; // this variable will use for database;
int eFound = -1; // this variable will use for email checking;
int emailValid=0;
int phFound = -1;
int spaceArray[100];
int temp = 0;

void loading();
void allDataPrinting();
void spaceCounting();
int charCounting(char toCount[50]);
void recordingDataToFile();
void register_fun();
void login();
void menu();
void emailExitChecking(char lEmail[50]);
void emailValidation(char email[50]);
//void userNameChecking(char toUser[50]);
void userProfileAndMenu(int userDBIndex);
void updateName();
void updatePass(int userDBIndex);
void updateEmail();
void updatePhNo();
void toTransfer(int userDBIndex);
void deposit(int userDBIndex);
void withdraw(int userDBIndex);
void phNumberChecking(unsigned int to_Phnumber);
int passwordCheck(char cPass[50], char dPass[50]);
int count_pass(char c_pass[50]);
int strong_pass(char s_pass[50]);
int nameCheck(char cName[50], char dName[50]);
void id_check(int user_id);
void adminSector();
void adminSector_2();
void adminSector_3();
void admin_delete();
void admin_update();
void admin_suspend();
void remove_ban();
int suspend(int num);


int main(){
    spaceCounting();
    loading();

    allDataPrinting();
    menu();

    return 0;
}

void spaceCounting(){
    FILE *fptr = fopen("8-db.txt","r");
    char c = fgetc(fptr);
    int index=0;
    while (!feof(fptr)){
        if(c!='\n'){
            if(c == ' '){
                spaceArray[index] +=1;
            }
            c = fgetc(fptr);

        }else{
            index++;
            c = fgetc(fptr);
        }
    }
    for(int i=0; i<index ; i++){
        printf("%d : ",spaceArray[i]);
    }
    printf("\n");
    fclose(fptr);
}

//This function will get all data from file
// and will insert to our database
void loading(){
    FILE *fptr = fopen("8-db.txt","r");
    if(fptr!= NULL){
        for(int i=0; i<USIZE ; i++){
//            if(db[i].id != db[i-1].id) {
                fscanf(fptr, "%u%s%s%s%u%s%u%s%s", &db[i].id, &db[i].name[0], &db[i].email[0], &db[i].password[0],
                       &db[i].phNumber, &db[i].address[0],
                       &db[i].amount, &db[i].ban[0], &db[i].note[0]);
                if (i <= 2) {
                    for (int gcc = 0; gcc < (spaceArray[i] - 8) / 3; gcc++) {
                        fscanf(fptr, "%s", &db[i].transRC[gcc].note_1[0]);
                        //fscanf(fptr, "%u", &db[i].transRC[gcc].rcAmount);
                        fscanf(fptr, "%s", &db[i].transRC[gcc].note_2[0]);
                        fscanf(fptr, "%s", &db[i].transRC[gcc].note_3[0]);
                    }
                } else {
                    for (int gcc = 0; gcc < (spaceArray[i] - 8) / 4; gcc++) {
                        fscanf(fptr, "%s", &db[i].transRC[gcc].note_1[0]);
                        fscanf(fptr, "%u", &db[i].transRC[gcc].rcAmount);
                        fscanf(fptr, "%s", &db[i].transRC[gcc].note_2[0]);
                        fscanf(fptr, "%s", &db[i].transRC[gcc].note_3[0]);
                    }
                }
                if (db[i].id == 0) {
                    break;
                }
                gIndex++;
           // }
        }
        printf("Loading Complete.\n");
    } else{
        printf("Loading failed at Loading Function():\n");
    }
    fclose(fptr);
}

void allDataPrinting(){
    for(int i=0; i<gIndex ; i++){
        printf("%u-%s-%s-%s-%u-%s-%u-%s-%s",db[i].id, db[i].name, db[i].email, db[i].password, db[i].phNumber,
               db[i].address, db[i].amount, db[i].ban, db[i].note);
        for(int gcc=0; gcc<=(spaceArray[i]-9)/4 ; gcc++){

            printf("-%s",db[i].transRC[gcc].note_1);
            if(db[i].transRC[gcc].rcAmount != 0) {
                printf("-%u", db[i].transRC[gcc].rcAmount);
            }
            printf("-%s",db[i].transRC[gcc].note_2);
            printf("-%s",db[i].transRC[gcc].note_3);
        }
        printf("\n");
    }
}

void recordingDataToFile(){

    FILE *fptr= fopen("8-db.txt","w");
    if(fptr == NULL){
        printf("file opening error at recordingToFile Function():\n");
    } else{
        for(int ncc=0; ncc<gIndex; ncc++){
            if(db[ncc].id != 0 && db[ncc].id != db[ncc-1].id) {
                fprintf(fptr, "%u%c%s%c%s%c%s%c%u%c%s%c%u%c%s%c%s", db[ncc].id, ' ', db[ncc].name, ' ', db[ncc].email,
                        ' ', db[ncc].password, ' ', db[ncc].phNumber,
                        ' ', db[ncc].address, ' ', db[ncc].amount, ' ', db[ncc].ban, ' ', db[ncc].note);
                printf("%u%c%s%c%s%c%s%c%u%c%s%c%u%c%s%c%s", db[ncc].id, ' ', db[ncc].name, ' ', db[ncc].email, ' ',
                       db[ncc].password, ' ', db[ncc].phNumber,
                       ' ', db[ncc].address, ' ', db[ncc].amount, ' ', db[ncc].ban, ' ', db[ncc].note);
                if(ncc<=2){
                    for(int gcc=0; gcc<(spaceArray[ncc]-8)/3; gcc++){
                        fprintf(fptr, "%c%s", ' ', db[ncc].transRC[gcc].note_1);
                        fprintf(fptr, "%c%s", ' ', db[ncc].transRC[gcc].note_2);
                        fprintf(fptr, "%c%s", ' ', db[ncc].transRC[gcc].note_3);
                    }
                }else {
                    for (int gcc = 0; gcc < (spaceArray[ncc] - 8) / 4; gcc++) {

                        fprintf(fptr, "%c%s", ' ', db[ncc].transRC[gcc].note_1);
                        printf("%c%s", ' ', db[ncc].transRC[gcc].note_1);
                        if (db[ncc].transRC[gcc].rcAmount != 0) {
                            fprintf(fptr, "%c%u", ' ', db[ncc].transRC[gcc].rcAmount);
                            printf("%c%u", ' ', db[ncc].transRC[gcc].rcAmount);
                        }
                        fprintf(fptr, "%c%s", ' ', db[ncc].transRC[gcc].note_2);
                        fprintf(fptr, "%c%s", ' ', db[ncc].transRC[gcc].note_3);
                        printf(" %s", db[ncc].transRC[gcc].note_2);
                        printf(" %s", db[ncc].transRC[gcc].note_3);
                    }
                }
                fprintf(fptr, "%c", '\n');
                printf(" %c", '\n');
            }

        }
        printf("Data recorded completely to '8-db.txt' File!\n");
    }
    fclose(fptr);
}

int charCounting(char toCount[50]){
    int charCount=0;
    for(int ncc=0; ncc<50; ncc++){

        if(toCount[ncc] == '\0'){
            break;
        } else{
            charCount++;
        }
    }
    return charCount;
}

void menu(){
    printf("\n$$$$$$$>>Welcome To MIRACLE BANK!<<$$$$$$$\n");
    char passA[13] = {'W','e','a','k','_','p','a','s','S','1','3','7','5'};
    for(int i=0; i<13; i++){
        db->RPass.rPassword[i] = passA[i];
    }
    char menuOption[10];
    printf("[r] For Register!\n");
    printf("[l] For Login!\n");
    printf("[e] to Exit!\n");
    printf("Enter your option:");
    scanf(" %[^\n]",&menuOption[0]);
    int count_1 = charCounting(menuOption);
    if(count_1>1){
        printf("Invalid Option!\n");
        menu();
    }else {
        if (menuOption[0] == 'l') {
            printf("\nLogin Session...\n");
            login();
        } else if (menuOption[0] == 'r') {
            printf("\nRegister Session...\n");
            register_fun();
        } else if (menuOption[0] == 'e') {
            recordingDataToFile();
            exit(1);
        } else {
            printf("Invalid Option:\n");
            menu();
        }
    }
}

void register_fun(){

    char rEmail[50];
    printf("Enter your email    :");
    scanf(" %[^\n]",&rEmail[0]);

    emailValid = 0;
    emailValidation(rEmail);
    if( emailValid != -1){
        eFound=-1;
        emailExitChecking(rEmail);
        int newUserIndex = gIndex;
        if(eFound == -1){
            int toInsertDb_email = charCounting(rEmail);
            for(int z=0; z<toInsertDb_email ; z++){
                db[newUserIndex].email[z] = rEmail[z];
            }
            db[newUserIndex].id = db[newUserIndex-1].id + 1;

            printf("Enter your username :");
            scanf(" %[^\n]",&db[newUserIndex].name[0]);
            int count_1 = charCounting(db[newUserIndex].name);
            for(int i=0; i<count_1; i++){
                if(db[newUserIndex].name[i] == ' '){
                    db[newUserIndex].name[i] = '-';
                }
            }
            printf("Enter your password :");
            scanf(" %[^\n]",&db[newUserIndex].password[0]);
            int receiver1 = count_pass(db[newUserIndex].password);
            int receiver2 = strong_pass(db[newUserIndex].password);
            if(receiver1 >= 8 && receiver2 == 10) {
                phFound = -1;
                printf("Enter your phone number :");
                scanf("%u", &db[newUserIndex].phNumber);
                if(db[newUserIndex].phNumber >= 959100000 && db[newUserIndex].phNumber <= 959999999) {
                    phNumberChecking(db[newUserIndex].phNumber);
                    if (phFound == -1) {
                        printf("Address also please :");
                        scanf(" %[^\n]", &db[newUserIndex].address[0]);
                        int count_2 = charCounting(db[newUserIndex].address);
                        for(int j=0; j<count_2; j++){
                            if(db[newUserIndex].address[j] ==' '){
                                db[newUserIndex].address[j] = '-';
                            }
                        }
                        printf("Enter your initial amount :");
                        scanf("%u", &db[newUserIndex].amount);
                        printf("Some reason for your account :");
                        scanf(" %[^\n]", &db[newUserIndex].note[0]);
                        int count_3 = charCounting(db[newUserIndex].note);
                        for(int k=0; k<count_3; k++){
                            if(db[newUserIndex].note[k] ==' '){
                                db[newUserIndex].note[k] = '-';
                            }
                        }
                        char accept[5] = {'a','l','l','o','w'};
                        for(int i=0; i<5; i++){
                            db[newUserIndex].ban[i] = accept[i];
                        }
                        printf("Complete Registration!\n");
                        gIndex++;
                        spaceArray[newUserIndex] +=8;
                        allDataPrinting();
                        menu();
                    } else {
                        printf("Phone Number already Registered.\n");
                        register_fun();
                    }
                }else{
                    printf("Not a Format Number!\nPls starts with '959'......\n");
                    register_fun();
                }
            }else{
                printf("Password Too Weak.\nMust contain at least 8 counts.\nEach one Capital letter, Small letter, Special Character and Number!");
                register_fun();
            }

        } else{
            printf("Your email has been already registered:\n");
            register_fun();
        }
    } else{
        printf("Email format not valid :\n");
        register_fun();
    }
}

void login() {
    char aPass[50];
    char lPass[50];
    char l_email[50];
    printf("Enter your email address :");
    scanf(" %[^\n]", &l_email[0]);
    eFound = -1;
    emailExitChecking(l_email);
    int flag = suspend(eFound);
    if (flag == 1) {
        printf("This Account has been suspended by Admin!!!\n");
        //recordingDataToFile();
        menu();
    } else {
        if (eFound >= 0 && eFound <= 2) {
            printf("Enter Your Password      :");
            scanf(" %[^\n]", &aPass[0]);
            int receive = passwordCheck(aPass, db[eFound].password);
            if (receive == 1) {
                printf("\nWelcome Admin...\n");
                printf("All of Actions are shall be liable to you:\n");
                if(eFound == 0) {
                    temp = eFound;
                    adminSector();
                }else if(eFound == 1){
                    temp = eFound;
                    adminSector_2();
                }else if(eFound == 2){
                    temp = eFound;
                    adminSector_3();
                }
            } else {
                printf("Incorrect Password.\n");
                login();
            }
        }
        if (eFound != -1 && eFound > 2) {
            printf("your email found!\n");
            printf("Enter Your Password :");
            scanf(" %[^\n]", &lPass[0]);
            int receive = passwordCheck(lPass, db[eFound].password);
            if (receive == 1) {
                printf("Login Success...\n");
                userProfileAndMenu(eFound);
                menu();
            } else {
                printf("Incorrect Password...\n");
                menu();
            }
        } else {
            printf("Email not found.\nPls try again :\n");
            menu();
        }
    }
}

void emailExitChecking(char lEmail[50]){
    int loginEmailCount=charCounting(lEmail);
    for(int ncc=0; ncc<gIndex; ncc++){
        int dbEmailCount =0;
        dbEmailCount = charCounting(db[ncc].email);

        int sameCount=0;
        if( loginEmailCount == dbEmailCount){
            for(int i=0; i<loginEmailCount ; i++){
                if(db[ncc].email[i] == lEmail[i]){
                    sameCount++;
                } else{
                    break;
                }
            }
            if(dbEmailCount == sameCount){
                eFound=ncc;
                return;
            }
        }
    }
}

void emailValidation(char email[50]) {

    char emailForm[10] = {'@', 'g', 'm', 'a', 'i', 'l', '.', 'c', 'o', 'm'};
//    char capital_l[27] = {'A', 'B', 'C', 'D', 'E', 'F','G','H','I','J','K','L','M',
//                          'N','O','P','Q','R','S','T','U','V','W','X','Y','Z',' '};
    int count_1 = charCounting(email);
    int cCount = 0;
    for (int a = 0; a < 50; a++) {
        if (email[a] == '@') {
            break;
        } else {
            cCount++;
        }
    }
    int formIndex = 0;
    for (int i = 0; i < count_1; i++) {

            if (email[i] == ' ' || email[0] == '.') {
                emailValid = -1;
                break;

        }
    }
    for (int b = cCount; b < cCount + 10; b++) {
        if (email[b] != emailForm[formIndex] || email[cCount] == '.') {
            emailValid = -1;
            break;
        }
        formIndex++;
    }
}

void userProfileAndMenu(int userDBIndex){
    char option[10];
    printf("\nWelcome Mr/s %s...\n", db[userDBIndex].name);
    printf("Your Information >>\n");
    printf("Email    : %s\n",db[userDBIndex].email);
    printf("Username : %s\n",db[userDBIndex].name);
    printf("PhNumber : %u\n",db[userDBIndex].phNumber);
    printf("Amount   : %u\n\n",db[userDBIndex].amount);

    printf("Press 'p' to Update Password:\n");
    printf("Press 't' to Transfer:\n");
    printf("Press 'd' to Deposit:\n");
    printf("Press 'w' to Withdraw:\n");
    printf("Press any other key to exit :");

    scanf(" %[^\n]",&option[0]);
    int count_1 = charCounting(option);
    if(count_1>1){
        printf("Invalid Option!\n");
        userProfileAndMenu(userDBIndex);
    }else {
        if (option[0] == 'p') {
            printf("Account Update Session...\n");
            updatePass(userDBIndex);

        } else if (option[0] == 't') {
            printf("Money Transfer Session...\n");
            toTransfer(userDBIndex);
        } else if (option[0] == 'd') {
            printf("Deposit Session...\n");
            deposit(userDBIndex);
        } else if (option[0] == 'w') {
            printf("Withdraw Session...\n");
            withdraw(userDBIndex);
        } else {
            menu();
        }
    }
}

void updatePass(int userDBIndex) {
    char uPass[50];
    char cPass[50];
    //char nPass[50];
    printf("Enter Your Current Password :");
    scanf(" %[^\n]", &uPass[0]);
    int receive = passwordCheck(uPass, db[userDBIndex].password);
    if (receive == 1) {
        printf("Enter New Password :");
        scanf(" %[^\n]", &cPass[0]);
        int receive_1 = strong_pass(cPass);
        if (receive_1 == 10) {
            int receive2 = passwordCheck(cPass, db[userDBIndex].password);
            if (receive2 != 1) {
                int countP = 0;
                for (int i = 0; i < 50; i++) {
                    if (cPass[i] != '\0') {
                        countP++;
                    } else {
                        break;
                    }
                }
                for (int j = 0; j < countP; j++) {
                    db[userDBIndex].password[j] = cPass[j];
                }
                for (int k = countP; k < 50; k++) {
                    db[userDBIndex].password[k] = '\0';
                }
                printf("Password Updated...\n");
                userProfileAndMenu(userDBIndex);
            } else {
                printf("Enter another different password.\n");
                updatePass(userDBIndex);
            }
        } else {
            printf("Password Too Weak.\n");
            updatePass(userDBIndex);
        }
    } else {
        printf("Incorrect Password!!! try again...\n");
        updatePass(userDBIndex);
    }
}

void toTransfer(int userDBIndex) {
    unsigned int toUserPh = 0;
    printf("Pls enter PhNumber to send money for:");
    scanf("%u", &toUserPh);
    phFound = -1;
    phNumberChecking(toUserPh);
    if (phFound != -1 && phFound > 3) {
        int flag = suspend(phFound);
        if (flag != 1) {
            unsigned int toAmount = 0;
            char tPass[50];
            printf("U can transfer to %s-(%u)\n", db[phFound].name, db[phFound].phNumber);
            printf("Please enter amount to send    :");
            scanf("%u", &toAmount);

            if (toAmount <= db[userDBIndex].amount - 1000 && toAmount > 0) {
                printf("Enter your password to confirm :");
                scanf(" %[^\n]", &tPass[0]);
                int receive = passwordCheck(tPass, db[userDBIndex].password);
                if (receive == 1) {
                    db[userDBIndex].amount = db[userDBIndex].amount - toAmount; // လွှဲမည့်သူ   transferer
                    db[phFound].amount += toAmount; // လက်ခံမည့်သူ
                    char toInsert1[15] = {'T','r','a','n','s','f','e','r','r','e','d','-','T','o','-'};
                    char toInsert6[7] = {'T', 'i', 'm', 'e', '.', '.', '.'};
                    //db[userDBIndex].transRC[spaceArray[userDBIndex]].note
                    int transfer = charCounting(db[userDBIndex].name);
                    int accept = charCounting(db[phFound].name);

                    for (int x = 0; x < 15; x++) {
                        db[userDBIndex].transRC[(spaceArray[userDBIndex] - 8)/4].note_1[x] = toInsert1[x];
                    }
                    int nameIndex = 0;
                    for (int x = 15; x < accept + 15; x++) {
                        db[userDBIndex].transRC[(spaceArray[userDBIndex] - 8)/4].note_1[x] = db[phFound].name[nameIndex];
                        nameIndex++;
                    }
                    db[userDBIndex].transRC[(spaceArray[userDBIndex] - 8)/4].rcAmount = toAmount;
                    for (int x = 0; x < 7; x++) {
                        db[userDBIndex].transRC[(spaceArray[userDBIndex] - 8)/4].note_2[x] = toInsert6[x];
                    }
                    time_t raw_time;
                    struct tm *info;
                    time( &raw_time );
                    info = localtime( &raw_time );

                    strftime(db[userDBIndex].transRC[(spaceArray[userDBIndex] - 8)/4].note_3,100,"%d/%b/%Y-%I:%M%p", info);
                    ////////
                    char to_insert2[14] = {'R','e','c','e','i','v','e','d','-','F','r','o','m','-'};
                    for (int x = 0; x < 14; x++) {
                        db[phFound].transRC[(spaceArray[phFound] - 8)/4].note_1[x] = to_insert2[x];
                    }
                    nameIndex = 0;
                    for (int x = 14; x < transfer + 14; x++) {
                        db[phFound].transRC[(spaceArray[phFound] - 8)/4].note_1[x] = db[userDBIndex].name[nameIndex];
                        nameIndex++;
                    }
                    db[phFound].transRC[(spaceArray[phFound] - 8)/4].rcAmount = toAmount;
                    for (int x = 0; x < 7; x++) {
                        db[phFound].transRC[(spaceArray[phFound] - 8)/4].note_2[x] = toInsert6[x];
                    }
                    strftime(db[phFound].transRC[(spaceArray[phFound]-8)/4].note_3, 100, "%d/%b/%Y-%I:%M%p", info);
                    spaceArray[userDBIndex] = spaceArray[userDBIndex] + 4;
                    spaceArray[phFound] = spaceArray[phFound] + 4;
                    //allDataPrinting();

                    char option[10];
                    printf("\nTransaction was successful!\n");
                    printf("Your amount for now :%u\n", db[userDBIndex].amount);
                    printf("Receiver amount     :%u\n\n", db[phFound].amount);
                    printf("Press 'u' to User Profile:\n");
                    printf("Press 'e' to Exit:\n");
                    printf("Press 'm' to Menu:\n");

                    scanf(" %[^\n]", &option[0]);
                    int count_1 = charCounting(option);
                    if(count_1>1){
                        printf("Invalid Option!\n");
                        userProfileAndMenu(userDBIndex);
                    }else {
                        if (option[0] == 'u') {
                            userProfileAndMenu(userDBIndex);
                        } else if (option[0] == 'e') {
                            recordingDataToFile();
                            exit(1);
                        } else if (option[0] == 'm') {
                            menu();
                        } else {
                            printf("Invalid Option:\n");
                            userProfileAndMenu(userDBIndex);
                        }
                    }
                } else {
                    printf("Incorrect Password.\n");
                    toTransfer(userDBIndex);
                }
            } else {
                printf("Insufficient Amount!\n");
                toTransfer(userDBIndex);
            }
        } else {
            printf("This Number has been suspended by Admin!!!\n");
            userProfileAndMenu(userDBIndex);
        }

    } else {
        printf("User Phone Number not Found!\n");
        toTransfer(userDBIndex);
    }
}

void deposit(int userDBIndex){
    unsigned int deAmount;
    char dePass[50];
    time_t raw_time;
    struct tm *info;
    time( &raw_time );
    info = localtime( &raw_time );

    printf("Enter the amount you want to deposit :");
    scanf(" %u", &deAmount);
    if(deAmount > 0) {
        printf("Enter your password to confirm       :");
        scanf(" %[^\n]", &dePass[0]);
        int receive = passwordCheck(dePass, db[userDBIndex].password);
        if (receive == 1) {
            db[userDBIndex].amount = db[userDBIndex].amount + deAmount;

            char to_insert[10] = {'D','e','p','o','s','i','t','e','d','-'};
            char to_insert2[7] = {'T','i','m','e','.','.','.'};
            for(int i=0; i<10; i++){
                db[userDBIndex].transRC[(spaceArray[userDBIndex]-8)/4].note_1[i] = to_insert[i];
            }
            db[userDBIndex].transRC[(spaceArray[userDBIndex]-8)/4].rcAmount = deAmount;
            for(int j=0; j<7; j++){
                db[userDBIndex].transRC[(spaceArray[userDBIndex]-8)/4].note_2[j] = to_insert2[j];
            }
            strftime(db[userDBIndex].transRC[(spaceArray[userDBIndex]-8)/4].note_3, 100, "%d/%b/%Y-%I:%M%p", info);
            spaceArray[userDBIndex] += 4;
            printf("Deposit Complete.\n");
            printf("Your Updated Amount : %u\n", db[userDBIndex].amount);
            userProfileAndMenu(userDBIndex);
        } else {
            printf("Incorrect password.\ntry again...\n");
            deposit(userDBIndex);
        }
    }else{
        printf("Invalid Amount.\ntry again...\n");
        deposit(userDBIndex);
    }
}

void withdraw(int userDBIndex){
    unsigned int wAmount;
    char wPass[50];
    time_t raw_time;
    struct tm *info;
    time( &raw_time );
    info = localtime( &raw_time );
    printf("Enter the amount you want to withdraw :");
    scanf(" %u", &wAmount);
    if(wAmount > 0 && wAmount <= db[userDBIndex].amount-1000) {
        printf("Enter your password to confirm        :");
        scanf(" %[^\n]", &wPass);
        int receive = passwordCheck(wPass, db[userDBIndex].password);
        if (receive == 1) {
            db[userDBIndex].amount = db[userDBIndex].amount - wAmount;
            db[userDBIndex].amount = db[userDBIndex].amount - wAmount/200;
            db[0].amount = db[0].amount + wAmount/200;
            char to_insert[9] = {'W','i','t','h','d','r','e','w','-'};
            char to_insert2[7] = {'T','i','m','e','.','.','.'};
            for(int i=0; i<9; i++){
                db[userDBIndex].transRC[(spaceArray[userDBIndex]-8)/4].note_1[i] = to_insert[i];
            }
            db[userDBIndex].transRC[(spaceArray[userDBIndex]-8)/4].rcAmount = wAmount;
            for(int j=0; j<7; j++){
                db[userDBIndex].transRC[(spaceArray[userDBIndex]-8)/4].note_2[j] = to_insert2[j];
            }
            strftime(db[userDBIndex].transRC[(spaceArray[userDBIndex]-8)/4].note_3, 100, "%d/%b/%Y-%I:%M%p", info);
            spaceArray[userDBIndex] += 4;
            char a = '%';
            printf("Money Withdrew.\n");
            printf("We Take 0.5%c of Withdrew Amount - %u\n",a,wAmount/200);
            printf("Your Updated Amount : %u\n", db[userDBIndex].amount);
            userProfileAndMenu(userDBIndex);
        } else {
            printf("Incorrect password.\ntry again...\n");
            withdraw(userDBIndex);
        }
    }else{
        printf("Invalid Amount.\ntry again...\n");
        withdraw(userDBIndex);
    }
}

void phNumberChecking(unsigned int to_Phnumber){

    for(int i=0; i<gIndex ; i++){

        if(db[i].phNumber == to_Phnumber){

            phFound = i;
            //break;
        }
    }
}

int passwordCheck(char cPass[50], char dPass[50]){
    int countT=0;
    int countO=0;
    int sameC=0;
    int returnC=0;
    for(int i=0; i<50; i++){
        if(cPass[i]!='\0'){
            countT++;
        }else{
            break;
        }
    }
    for(int i=0; i<50; i++){
        if(dPass[i]!='\0'){
            countO++;
        }else{
            break;
        }
    }
    if(countT==countO){
        for(int j=0; j<countT; j++){
            if(cPass[j]==dPass[j]){
                sameC++;
            }else{
                break;
            }
        }
    }
    if(sameC==countT){
        returnC=1;
    }else{
        returnC=-1;
    }
    return returnC;
}

int count_pass(char c_pass[50]){
    int count_p=0;
    for(int i=0; i<50; i++){
        if(c_pass[i] == '\0'){
            break;
        }else{
            count_p++;
        }
    }
    return count_p;
}

int strong_pass(char s_pass[50]){
    int capital_c=0;
    int small_c=0;
    int special_c=0;
    int number_c=0;
    char capital_l[26] = {'A', 'B', 'C', 'D', 'E', 'F','G','H','I','J','K','L','M',
                        'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

    char small_l[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n',
                        'o','p','q','r','s','t','u','v','w','x','y','z'};

    char special_l[29] = {'!','@','#','$','%','^','&','*','`','~','(',')','<','>','/',
                        '*','-','+','|','[',']','{','}',',','.',';',':','?','"'};

    char number_l[10] = {'1','2','3','4','5','6','7','8','9','0'};
    int count_c = count_pass(s_pass);
    for(int i=0; i<count_c; i++) {
        for (int j = 0; j < 26; j++) {
            if (s_pass[i] == capital_l[j]) {
                capital_c = 1;
            }
        }
        for (int k = 0; k < 26; k++) {
            if (s_pass[i] == small_l[k]) {
                small_c = 2;
            }
        }
        for (int l = 0; l < 29; l++) {
            if (s_pass[i] == special_l[l]) {
                special_c = 3;
            }
        }
        for (int h = 0; h < 10; h++) {
            if (s_pass[i] == number_l[h]) {
                number_c = 4;
            }
        }
    }
    int s = capital_c + small_c + special_c + number_c;
    return s;
}

int nameCheck(char cName[50], char dName[50]){
    int countA=0;
    int countB=0;
    int same_C=0;
    int returnNC=0;
    for(int i=0; i<50; i++){
        if(cName[i]!='\0'){
            countA++;
        }else{
            break;
        }
    }
    for(int i=0; i<50; i++){
        if(dName[i]!='\0'){
            countB++;
        }else{
            break;
        }
    }
    if(countA==countB){
        for(int j=0; j<countA; j++){
            if(cName[j]==dName[j]){
                same_C++;
            }else{
                break;
            }
        }
    }
    if(same_C==countA){
        returnNC=1;
    }else{
        returnNC=-1;
    }
    return returnNC;
}

void id_check(int user_id){
    for(int i=0; i<gIndex; i++){
        if(db[i].id == user_id) {
            user_id = i;
            break;
        }
//       }else{
//            user_id = -1;
//        }
    }
}

void adminSector(){
    char admin_Option[10];
    printf("Press 1 to Delete User Account:\n");
    printf("Press 2 to Update Information of user:\n");
    printf("Press 3 to Suspend User Account:\n");
    printf("Press 4 to Remove Banned Accounts from ban list.\n");
    printf("Press 5 to Exit!\n");
    printf("Press your option carefully:");
    scanf(" %[^\n]",&admin_Option[0]);

    int count_1 = charCounting(admin_Option);
    if(count_1>1){
        printf("Invalid Option.\n");
        adminSector();
    }else {
        if (admin_Option[0] == '1') {
            printf("Delete Session for admin...\n");
            admin_delete();
        } else if (admin_Option[0] == '2') {
            printf("Update Session for admin...\n");
            admin_update();
        } else if (admin_Option[0] == '3') {
            printf("Suspend Session for admin...\n");
            admin_suspend();
        }else if(admin_Option[0] == '4'){
            printf("AntiBan...\n");
            remove_ban();
        }else if (admin_Option[0] == '5') {
            printf("Good Luck!\n");
            //recordingDataToFile();
            menu();
        } else {
            printf("Invalid Option.\nPls Try Again!\n");
            adminSector();
        }
    }
}

void adminSector_2(){
    char admin_Option2[10];
    printf("Press 1 to Delete User Account:\n");
    printf("Press 2 to Suspend User Account:\n");
    printf("Press 3 to Remove Banned Accounts from ban list.\n");
    printf("Press 4 to Exit!\n");
    printf("Press your option carefully:");
    scanf(" %[^\n]",&admin_Option2[0]);

    int count_1 = charCounting(admin_Option2);
    if(count_1>1){
        printf("Invalid Option.\n");
        adminSector_2();
    }else{
        if(admin_Option2[0] == '1'){
            printf("Delete Session for admin...\n");
            admin_delete();
        }
        else if(admin_Option2[0] == '2'){
            printf("Suspend Session for admin...\n");
            admin_suspend();
        }else if(admin_Option2[0] == '3'){
            printf("AntiBan...\n");
            remove_ban();
        }else if(admin_Option2[0] == '4'){
            printf("Good Luck!\n");
            menu();
        }else{
            printf("Invalid Option.\n");
            adminSector_2();
        }
    }
}

void adminSector_3(){
    printf("Update Session For Admin...\n");
    admin_update();
}

void admin_delete() {
    char delEmail[50];
    unsigned int delPh;
    char delPass[50];
    printf("Type an email address to delete  :");
    scanf(" %[^\n]", &delEmail[0]);
    eFound = -1;
    emailExitChecking(delEmail);
    if (eFound != -1 && eFound > 2) {
        printf("Type user's phone number if sure :");
        scanf(" %u", &delPh);
        phFound = -1;
        phNumberChecking(delPh);
        if (phFound == eFound) {
            printf("Type admin password to confirm deletion :");
            scanf(" %[^\n]", &delPass[0]);
            int receive = passwordCheck(delPass, db->RPass.rPassword);
            if (receive == 1) {
                db[eFound].id = 0;
                if(eFound==gIndex-1) {
                    gIndex--;
                }

                char a_delete[14] = {'A','d','m','i','n','-','d','e','l','e','t','e','d','-'};
                char b_delete[8] = {'-','A','c','c','o','u','n','t'};
                char c_delete[7] = {'T','i','m','e','.','.','.'};
                for(int x=0; x<14; x++){
                    db[temp].transRC[(spaceArray[temp]-8)/3].note_1[x] = a_delete[x];
                }
                int count_1 = charCounting(db[eFound].name);
                int a = 14;
                for(int y=0; y<count_1; y++){
                    db[temp].transRC[(spaceArray[temp]-8)/3].note_1[a] = db[eFound].name[y];
                    a++;
                }
                int b = 14+count_1;
                for(int z=0; z<8; z++){
                    db[temp].transRC[(spaceArray[temp]-8)/3].note_1[b] = b_delete[z];
                    b++;
                }
                for(int i=0; i<7; i++){
                    db[temp].transRC[(spaceArray[temp]-8)/3].note_2[i] = c_delete[i];
                }
                time_t raw_time;
                struct tm *info;
                time( &raw_time );
                info = localtime( &raw_time );
                strftime(db[temp].transRC[(spaceArray[temp]-8)/3].note_3, 100, "%d/%b/%Y-%I:%M%p", info);
                spaceArray[temp] += 3;
                int temp_int = gIndex;
                recordingDataToFile();
                gIndex = 0;
                loading();
                gIndex = temp_int - 1;
                printf("User Account Deleted.\n");
                if(temp == 0){
                    adminSector();
                }else{
                    adminSector_2();
                }
            } else {
                printf("Incorrect Password of Admin.\n");
                admin_delete();
            }
        } else {
            printf("User's Phone Number Wrong.\n");
            admin_delete();
        }
    } else {
        printf("Email not Found.\n");
        admin_delete();
    }
}

void admin_update(){
    char option[10];
    printf("Press 'u' to update username.\n");
    printf("Press 'p' to update phone number.\n");
    printf("Press 'e' to update email address.\n");
    printf("Press any other key to return.\n");
    scanf(" %[^\n]", &option[0]);
    int count_1 = charCounting(option);
    if(count_1>1){
        printf("Invalid Option.\n");
        admin_update();
    }else {
        switch (option[0]) {
            case 'u':
                printf("To Update Username...\n");
                updateName();
                break;
            case 'p':
                printf("To Update Phone Number...\n");
                updatePhNo();
                break;
            case 'e':
                printf("To Update Email Address...\n");
                updateEmail();
                break;
            default:
                if(temp == 0){
                    adminSector();
                }else if(temp == 1){
                    adminSector_2();
                }else{
                    adminSector_3();
                }
                break;
        }
    }
}

void updateName(){
    char uName[50];
    char cName[50];
    char nPass[50];
    int name_id;
    printf("Enter Current ID and Username:\n");
    scanf(" %d", &name_id);
    id_check(name_id);
    scanf(" %[^\n]", &uName[0]);
    int flag = suspend(name_id);
    if(name_id>2 && flag != 1) {
        int receive = nameCheck(uName, db[name_id].name);
        if (receive == 1) {
            printf("Enter New Username :");
            scanf(" %[^\n]", &cName[0]);
            int receive2 = nameCheck(cName, db[name_id].name);
            if (receive2 != 1) {
                printf("Enter root Password to Confirm :");
                scanf(" %[^\n]", &nPass[0]);
                int receive3 = passwordCheck(nPass, db->RPass.rPassword);
                if (receive3 == 1) {
                    int countN = 0;
                    for (int i = 0; i < 50; i++) {
                        if (cName[i] != '\0') {
                            countN++;
                        } else {
                            break;
                        }
                    }
                    for (int j = 0; j < countN; j++) {
                        db[name_id].name[j] = cName[j];
                    }
                    for (int k = countN; k < 50; k++) {
                        db[name_id].name[k] = '\0';
                    }
                    char insert_1[14] = {'A','d','m','i','n','-','u','p','d','a','t','e','d','-'};
                    char insert_2[14] = {'`','s','u','s','e','r','n','a','m','e','-','t','o','-'};
                    char insert_3[7] = {'T','i','m','e','.','.','.'};
                    for(int i=0; i<14; i++){
                        db[temp].transRC[(spaceArray[temp]-8)/3].note_1[i] = insert_1[i];
                    }
                    int a = charCounting(uName);
                    int b = 14;
                    for(int j=0; j<a; j++){
                        db[temp].transRC[(spaceArray[temp]-8)/3].note_1[b] = uName[j];
                        b++;
                    }
                    for(int k=0; k<14; k++){
                        db[temp].transRC[(spaceArray[temp]-8)/3].note_1[b] = insert_2[k];
                        b++;
                    }
                    int c = charCounting(cName);
                    for(int m=0; m<c; m++){
                        db[temp].transRC[(spaceArray[temp]-8)/3].note_1[b] = cName[m];
                        b++;
                    }
                    for(int l=0; l<7; l++){
                        db[temp].transRC[(spaceArray[temp]-8)/3].note_2[l] = insert_3[l];
                    }
                    time_t raw_time;
                    struct tm *info;
                    time(&raw_time);
                    info = localtime(&raw_time);
                    strftime(db[temp].transRC[(spaceArray[temp]-8)/3].note_3, 100, "%d/%b/%Y-%I:%M%p", info);
                    spaceArray[temp] += 3;
                    printf("Username Updated...\n");
                    admin_update();
                } else {
                    printf("Incorrect Password!!! try again...\n");
                    updateName();
                }
            } else {
                printf("Enter a different name.\n");
                updateName();
            }
        } else {
            printf("Invalid Id or Username.\n");
            updateName();
        }
    }else{
        printf("Invalid Id.\n");
        updateName();
    }
}

void updateEmail(){
    char uEmail[50];
    char cEmail[50];
    char pEmail[50];
    int email_id;
    printf("Enter Current ID and Email Address:\n");
    scanf(" %d", &email_id);
    id_check(email_id);
    scanf(" %[^\n]", &uEmail[0]);
    int flag = suspend(email_id);
    if(email_id>2 && flag!=1) {
    eFound = -1;
    emailExitChecking(uEmail);
    if(eFound == email_id){
        printf("Enter new Email Address :");
        scanf(" %[^\n]", &cEmail[0]);
        emailValid = 0;
        emailValidation(cEmail);
        if(emailValid != -1) {
            eFound = -1;
            emailExitChecking(cEmail);
            if (eFound == -1) {
                printf("Enter root Password to Confirm :");
                scanf(" %[^\n]", &pEmail[0]);
                int receive = passwordCheck(pEmail, db->RPass.rPassword);
                if (receive == 1) {
                    int countE = 0;
                    for (int i = 0; i < 50; i++) {
                        if (cEmail[i] != '\0') {
                            countE++;
                        } else {
                            break;
                        }
                    }
                    for (int j = 0; j < countE; j++) {
                        db[email_id].email[j] = cEmail[j];
                    }
                    for (int k = countE; k < 50; k++) {
                        db[email_id].email[k] = '\0';
                    }
                    char insert_1[14] = {'A','d','m','i','n','-','u','p','d','a','t','e','d','-'};
                    char insert_2[4] = {'-','t','o','-'};
                    char insert_3[7] = {'T','i','m','e','.','.','.'};
                    for(int i=0; i<14; i++){
                        db[temp].transRC[(spaceArray[temp]-8)/3].note_1[i] = insert_1[i];
                    }
                    int a = charCounting(uEmail);
                    int b = 14;
                    for(int j=0; j<a; j++){
                        db[temp].transRC[(spaceArray[temp]-8)/3].note_1[b] = uEmail[j];
                        b++;
                    }
                    for(int k=0; k<4; k++){
                        db[temp].transRC[(spaceArray[temp]-8)/3].note_1[b] = insert_2[k];
                        b++;
                    }
                    int c = charCounting(cEmail);
                    for(int m=0; m<c; m++){
                        db[temp].transRC[(spaceArray[temp]-8)/3].note_1[b] = cEmail[m];
                        b++;
                    }
                    for(int l=0; l<7; l++){
                        db[temp].transRC[(spaceArray[temp]-8)/3].note_2[l] = insert_3[l];
                    }
                    time_t raw_time;
                    struct tm *info;
                    time(&raw_time);
                    info = localtime(&raw_time);
                    strftime(db[temp].transRC[(spaceArray[temp]-8)/3].note_3, 100, "%d/%b/%Y-%I:%M%p", info);
                    spaceArray[temp] += 3;
                    printf("Email Address Updated.\n");
                    admin_update();
                } else {
                    printf("Password Wrong.\n");
                    updateEmail();
                }
            } else {
                printf("Email already exists.\nEnter a different email.\n");
                updateEmail();
            }
        }else{
            printf("Your email format is invalid.\n");
            updateEmail();
        }
    }else{
        printf("Email not found\n");
        updateEmail();
    }
    }else{
        printf("Invalid Id.\n");
        updateEmail();
    }
}

void updatePhNo(){
    unsigned int uPh;
    unsigned int nPh;
    char pPass[50];
    int pass_id;
    printf("Enter Current ID and Phone Number :\n");
    scanf(" %d", &pass_id);
    id_check(pass_id);
    scanf(" %u", &uPh);
    int flag = suspend(pass_id);
    if(pass_id>2 && flag != 1){
    phFound = -1;
    phNumberChecking(uPh);
    if(phFound == pass_id){
        printf("Enter new Phone Number :");
        scanf(" %u", &nPh);
        phFound = -1;
        phNumberChecking(nPh);
        if(phFound == -1){
            printf("Enter root Password to Confirm :");
            scanf(" %[^\n]", &pPass[0]);
            int receive = passwordCheck(pPass, db->RPass.rPassword);
            if(receive == 1){
                char insert_1[14] = {'A','d','m','i','n','-','u','p','d','a','t','e','d','-'};
                char insert_2[14] = {'`','s','P','h','o','n','e','-','N','u','m','b','e','r'};
                char insert_3[7] = {'T','i','m','e','.','.','.'};
                for(int i=0; i<14; i++){
                    db[temp].transRC[(spaceArray[temp]-8)/3].note_1[i] = insert_1[i];
                }
                int a = charCounting(db[phFound].name);
                int b = 14;
                for(int k=0; k<a; k++){
                    db[temp].transRC[(spaceArray[temp]-8)/3].note_1[b] = db[phFound].name[k];
                    b++;
                }
                for(int m=0; m<14; m++){
                    db[temp].transRC[(spaceArray[temp]-8)/3].note_1[b] = insert_2[m];
                    b++;
                }
                for(int l=0; l<7; l++){
                    db[temp].transRC[(spaceArray[temp]-8)/3].note_2[l] = insert_3[l];
                }
                time_t raw_time;
                struct tm *info;
                time(&raw_time);
                info = localtime(&raw_time);
                strftime(db[temp].transRC[(spaceArray[temp]-8)/3].note_3, 100, "%d/%b/%Y-%I:%M%p", info);
                spaceArray[temp] += 3;
                db[pass_id].phNumber = nPh;
                printf("Phone Number Updated...\n");
                admin_update();
            }else{
                printf("Password Wrong.\ntry again...\n");
                updatePhNo();
            }
        }else{
            printf("Phone Number already exists.\n");
            updatePhNo();
        }
    }else{
        printf("ID or Phone Number Wrong!\n");
        updatePhNo();
    }
    }else{
        printf("Invalid Id.\n");
        updatePhNo();
    }
}

void admin_suspend() {
    char sEmail[64];
    char sPass[50];
    char banned[6] = {'b','a','n','n','e','d'};
    printf("Type the email address to suspend :");
    scanf(" %[^\n]", &sEmail[0]);
    eFound = -1;
    emailExitChecking(sEmail);
    if (eFound != -1 && eFound > 1) {
        printf("Type Admin password to confirm    :");
        scanf(" %[^\n]", &sPass[0]);
        int receive = passwordCheck(sPass, db->RPass.rPassword);
        if (receive == 1) {
            for(int i=0; i<6; i++){
                db[eFound].ban[i] = banned[i];
            }
            char a_delete[16] = {'A','d','m','i','n','-','s','u','s','p','e','n','d','e','d','-'};
            char b_delete[10] = {'`','s','-','A','c','c','o','u','n','t'};
            char c_delete[7] = {'T','i','m','e','.','.','.'};
            for(int x=0; x<16; x++){
                db[temp].transRC[(spaceArray[temp]-8)/3].note_1[x] = a_delete[x];
            }
            int count_1 = charCounting(db[eFound].name);
            int a = 16;
            for(int y=0; y<count_1; y++){
                db[temp].transRC[(spaceArray[temp]-8)/3].note_1[a] = db[eFound].name[y];
                a++;
            }
            int b = 16+count_1;
            for(int z=0; z<10; z++){
                db[temp].transRC[(spaceArray[temp]-8)/3].note_1[b] = b_delete[z];
                b++;
            }
            for(int i=0; i<7; i++){
                db[temp].transRC[(spaceArray[temp]-8)/3].note_2[i] = c_delete[i];
            }
            time_t raw_time;
            struct tm *info;
            time( &raw_time );
            info = localtime( &raw_time );
            strftime(db[temp].transRC[(spaceArray[temp]-8)/3].note_3, 100, "%d/%b/%Y-%I:%M%p", info);
            spaceArray[temp] += 3;
            printf("User Account Suspended.\n");
            if(temp == 0){
                adminSector();
            }else{
                adminSector_2();
            }
        } else {
            printf("Password Incorrect.\ntry again...\n");
            admin_suspend();
        }
    } else {
        printf("Invalid Email.\ntry again...\n");
        admin_suspend();
    }
}

void remove_ban(){
    char a_ban[64];
    char a_pass[50];
    printf("Type email address to remove from ban list.\n");
    scanf(" %[^\n]", &a_ban[0]);
    eFound = -1;
    emailExitChecking(a_ban);
    if(eFound != -1 && eFound>1) {
        if (db[eFound].ban[0] != 'b') {
            printf("This email is not on ban list.\n");
            remove_ban();
        } else {
            printf("Type Admin password to confirm.");
            scanf(" %[^\n]", &a_pass[0]);
            int receive = passwordCheck(a_pass, db->RPass.rPassword);
            if (receive == 1) {
                char a_remove[5] = {'a', 'l', 'l', 'o', 'w'};
                for (int i = 0; i < 10; i++) {
                    db[eFound].ban[i] = a_remove[i];
                    if (i >= 5) {
                        db[eFound].ban[i] = '\0';
                    }
                }
                char insert_1[14] = {'A', 'd', 'm', 'i', 'n', '-', 'r', 'e', 'm', 'o', 'v', 'e', 'd', '-'};
                char insert_2[14] = {'-', 'f', 'r', 'o', 'm', '-', 'b', 'a', 'n', '-', 'l', 'i', 's', 't'};
                char insert_3[7] = {'T', 'i', 'm', 'e', '.', '.', '.'};
                for (int i = 0; i < 14; i++) {
                    db[temp].transRC[(spaceArray[temp] - 8) / 3].note_1[i] = insert_1[i];
                }
                int a = 14;
                int b = charCounting(db[eFound].name);
                for (int j = 0; j < b; j++) {
                    db[temp].transRC[(spaceArray[temp] - 8) / 3].note_1[a] = db[eFound].name[j];
                    a++;
                }
                for (int k = 0; k < 14; k++) {
                    db[temp].transRC[(spaceArray[temp] - 8) / 3].note_1[a] = insert_2[k];
                    a++;
                }
                for (int l = 0; l < 7; l++) {
                    db[temp].transRC[(spaceArray[temp] - 8) / 3].note_2[l] = insert_3[l];
                }
                time_t raw_time;
                struct tm *info;
                time(&raw_time);
                info = localtime(&raw_time);
                strftime(db[temp].transRC[(spaceArray[temp] - 8) / 3].note_3, 100, "%d/%b/%Y-%I:%M%p", info);
                spaceArray[temp] +=3;
                printf("User Account removed from ban list.\n");
                if(temp == 0){
                    adminSector();
                }else{
                    adminSector_2();
                }
            }
        }
    }
}

int suspend(int num){
    int warn=0;
    for (int x = 0; x < gIndex; x++) {
        if (db[num].ban[0] == 'b') {
            warn = 1;
            break;
        } else {
            warn = -1;
        }
    }
    return warn;
}

//hide password
