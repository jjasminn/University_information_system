#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define leschr 8
#define maxchar 200
#define max 100
typedef struct lesson{
    char course_name[leschr];       //Dersleri saklayacagim struct
    char fullname[maxchar];
    int credit;
    int capasity;
    long *students;//dinamik bellekte ogrenci nolari sirali saklanacak
    struct lesson *next;
} Lesson;

typedef struct student{                 //Ogrencileri saklayacagim struct
    long student_no;
    char name[maxchar];
    char surname[maxchar];
    int number_of_taken_course;
    int total_credit;
    struct student *next;
    struct student *prew;//cift yonlu
} Student;

typedef struct kayit{               //yapilan islemleri kaydeden structim Dosyaya kaydederken kolaylik sagliyor
    int ID;
    char coursename[leschr];
    long student_no;
    char date[maxchar];
    char situation[maxchar];
    struct kayit *next;//linked list seklinde ama herhangi bir siralama yok
} Kayit;


int Is_lesson_exist(Lesson *node,char new_course[leschr],int *index);//dersin varligini kontrol eder ve nerede oldugu hakkinda bilgi verir



void open_course(Lesson *node,char course_name[leschr],char fullname[maxchar],int credit,int capasity,int (*Is_lesson_exist)(Lesson *node,char new_course[leschr],int *index),int isfromfile,void (*Dosyaya_Kaydet)(Lesson *lnode,Student *snode,Kayit *knode));
//Ders acar once Lesson linkli listesinde sonra da Dosyaya ekler


void close_course(Lesson *node,char course_name[leschr],int (*Is_lesson_exist)(Lesson *node,char new_course[leschr],int *index),int isfromfile,void (*Dosyaya_Kaydet)(Lesson *lnode,Student *snode,Kayit *knode),Kayit *knode,Student *snode);
//Dersi kapatir once Lesson linked listini sonra Student linked listini en sonda Dosyalarda degisiklik yapar



int Is_student_exist(Student *node,long Number,int *index);//ogrencinin varligini kontrol eder, nerede oldugu hakkinda da bilgi verir


void add_student(Student *node,long no,char name[maxchar],char surname[maxchar],int (*Is_student_exist)(Student *node,long Number,int *index),int credit,int number_of_takencourse,int isfromfile,void (*Dosyaya_Kaydet)(Lesson *lnode,Student *snode,Kayit *knode));
//Yeni ogrenci ekler once Student linked listte sonra Dosyalarda degisiklik yapar



void del_student(Student *node,long no,int (*Is_student_exist)(Student *node,long Number,int *index),void (*Dosyaya_Kaydet)(Lesson *lnode,Student *snode,Kayit *knode),Kayit *knode);
//Ogrenciyi siler  once Students linked listte sonra Dosyalarda degisiklik yapar




int add_course(Student *snode,Lesson *lnode,long student_no,char course_name[leschr],int (*Is_lesson_exist)(Lesson *node,char new_course[leschr],int *indexl),int (*Is_student_exist)(Student *node,long Number,int *indexs),void (*Dosyaya_Kaydet)(Lesson *lnode,Student *snode,Kayit *knode),Kayit *knode,int isfromfile,char date[maxchar],int maxcredit,int maxtakencourse);
//Ogrenciye yeni ders ekler once Lesson linked listinde sonra Student linked listinde degisiklik yapar en sonDosyaya kaydeder


int del_course(Lesson *lnode,Student *snode,long stID,char lsID[leschr],int (*Is_lesson_exist)(Lesson *node,char new_course[leschr],int *indexl),int (*Is_student_exist)(Student *node,long Number,int *indexs),void (*Dosyaya_Kaydet)(Lesson *lnode,Student *snode,Kayit *knode),int isfromfile,char date[maxchar],Kayit * knode);
//Ogrencide ders siler once Lesson linked listinde sonra Student linked listinde degisiklik yapar en sonDosyaya kaydeder



void FileBegginning(int isempty[3]);
//Dosyalarin varligini kontrol eder Varsa icinin dolulugunu da degiskende saklar

void AttendanceSheet(Lesson *lnode);
//Her dersin sinif listesini Dosya olarak olusturur,

void Dosyaya_Kaydet(Lesson *lnode,Student *snode,Kayit *knode);
//Yapilan islemleri Dosyaya kaydeder

void StudentsSyllabus(Kayit *knode,char no[maxchar]);
//Ogrenciye ait der programi Dosya olarak olusturur



int main(){
    Lesson *les_node;
    Lesson *iterl;
    Lesson *freel;


    Student *stu_node;
    Student *iters;
    Student *frees;


    Kayit *nodek;
    Kayit *iterk;
    Kayit *freek;


    int i,j,no,totalcredit,number_of_course,*ind,index;
    ind=&index;
    char name[maxchar],surname[maxchar];
    int isfilesempty[3];
    
    
    

    
    les_node=(Lesson *) malloc (sizeof(Lesson));
    stu_node=(Student *) malloc (sizeof(Student));      //ilk dugum olustururldu
    nodek=(Kayit *)malloc (sizeof(Kayit));
    


    iterl=les_node;
    strcpy(iterl->course_name,"-1");                //Dugumler tamamen bos ise kontrolunu yapmak icin duzenlemeler
    strcpy(iterl->fullname,"");
    iters=stu_node;
    iters->student_no=-1;
    nodek->ID=-1;
    iterk=nodek;
    char notdate[]="-";
    



    
    
    char tmpc[maxchar],tmpc2[maxchar],tmpc3[maxchar];
    int tmp1,tmp2,tmp3;
    long tmpl1,tmpl,tmpl2,tmpl3;

    FileBegginning(isfilesempty); //Ilk basta Dosyalar duzenleniyor

    //En basta Dosyalarin ici bos degil ise icerikleri dugumlere eklemek icin bu islemler yapiliyor
    if(isfilesempty[0]==0){    //Ders Dosyasi ve Lesson dugumu duzenlemeleri
        FILE *dersfr=fopen("Dersler.txt","r+");
        fscanf(dersfr,"%[^,],%[^,],%[^,],%[^\n]\n",tmpc,tmpc,tmpc,tmpc);//en basi okundu
        fscanf(dersfr,"%[^,],%[^,],%d,%d\n",tmpc,tmpc2,&tmp1,&tmp2);
        strcpy(iterl->course_name,tmpc);
        strcpy(iterl->fullname,tmpc2);
        iterl->credit=tmp1;
        iterl->capasity=tmp2;                                       //Ilk dugumun degerlerini mainde vermeliyim
        iterl->students=(long *)malloc(sizeof(long));
        iterl->students[0]=-1;
        iterl->next=NULL;
        while(!feof(dersfr)){
            fscanf(dersfr,"%[^,],%[^,],%d,%d\n",tmpc,tmpc2,&tmp1,&tmp2);
            open_course(iterl,tmpc,tmpc2,tmp1,tmp2,Is_lesson_exist,1,Dosyaya_Kaydet);     //ilk dugumden sonrasini fonksiyonlarla ekleyebilirim 
        }
        fclose(dersfr);
    }
    
    if(isfilesempty[1]==0){//Ogrenciler Dosyasi ve Student dugumu duzenlemeleri
        FILE *ogrfr=fopen("Ogrenciler.txt","r+");

        fscanf(ogrfr,"%[^,],%[^,],%[^,],%[^,],%[^\n]\n",tmpc,tmpc,tmpc,tmpc,tmpc);//en basi okundu
        fscanf(ogrfr,"%ld,%[^,],%[^,],%d,%d\n",&tmpl1,tmpc,tmpc2,&tmp2,&tmp3);

        iters->student_no=tmpl1;
        strcpy(iters->name,tmpc);
        strcpy(iters->surname,tmpc2);
        iters->number_of_taken_course=tmp2;                                                     //yine ilk dugum mainde
        iters->total_credit=tmp3;
        iters->next=NULL;
        iters->prew=NULL;
        while(!feof(ogrfr)){
            fscanf(ogrfr,"%ld,%[^,],%[^,],%d,%d\n",&tmpl1,tmpc,tmpc2,&tmp2,&tmp3);  
            add_student(iters,tmpl1,tmpc,tmpc2,Is_student_exist,tmp3,tmp2,1,Dosyaya_Kaydet);        //ilk dugumden sonrasini fonksiyonlarda kaydediyorum
        }
        fclose(ogrfr);
      
    }
    if(isfilesempty[2]==0){//Kayit dosyasi ve dugumlerin duzenlemeleri
        FILE *kytfr=fopen("OgrenciDersKayit.txt","r+");
        fscanf(kytfr,"%[^,],%[^,],%[^,],%[^,],%[^\n]\n",tmpc,tmpc,tmpc,tmpc,tmpc);
        fscanf(kytfr,"%d,%[^,],%ld,%[^,],%[^\n]\n",&tmp1,tmpc,&tmpl,tmpc2,tmpc3);
        nodek->ID=tmp1;
        strcpy(nodek->coursename,tmpc);
        strcpy(nodek->date,tmpc2);
        strcpy(nodek->situation,tmpc3);                         //kayit dugumunun basi burda duzenleniyor
        nodek->student_no=tmpl;
        nodek->next=NULL;
        if(!strcmp(tmpc3,"KAYITLI")){//eger durum KAYITLI degil ise her hangi bir islem yapmaya gerek yok
            add_course(iters,iterl,tmpl,tmpc,Is_lesson_exist,Is_student_exist,Dosyaya_Kaydet,nodek,1,notdate,max,max);            //ilk dugumun durumu KAYITLI ise ogrenciye ders ekleniyor
        } 
        while(!feof(kytfr)){
            Kayit *new ;
            new=(Kayit *)malloc (sizeof(Kayit));
            iterk->next=new;
            iterk=iterk->next;//ilki girilmisti cunku zaten
            fscanf(kytfr,"%d,%[^,],%ld,%[^,],%[^\n]\n",&tmp1,tmpc,&tmpl,tmpc2,tmpc3);
            iterk->ID=tmp1;
            strcpy(iterk->coursename,tmpc);
            strcpy(iterk->date,tmpc2);
            strcpy(iterk->situation,tmpc3);                                                                                        //Kayit dugumu duzenlemeleri
            iterk->student_no=tmpl;
            
            if(!strcmp(tmpc3,"KAYITLI")){
                add_course(iters,iterl,tmpl,tmpc,Is_lesson_exist,Is_student_exist,Dosyaya_Kaydet,nodek,1,notdate,max,max);              //kayitta durum KAYITLI ise ders ogrenciye eklenir
            }
            else if(!strcmp(tmpc3,"BIRAKTI")){
                del_course(iterl,iters,tmpl,tmpc,Is_lesson_exist,Is_student_exist,Dosyaya_Kaydet,1,notdate,nodek);                        //durum   BIRAKTI  ise ders ogrenciden silinir
                                                                                                                                            //eger  durum bu ikisi disinda DERS_KAPANDI bir degisiklik yapilmaz
            }


        } 
        fclose(kytfr);
        iterk=nodek;//node tekrar en basina alindi


    }
    
    int secim,yanlis=1,kredi,kapasite;
    long numara;
    char lsID[leschr],isim[maxchar],soyisim[maxchar],date[maxchar];
    int maxcourse,maxcredit;                                                    //Menu de kullanilacak degiskenler
    int *index1,*index2,ind1,ind2;
    index1=&ind1;
    index2=&ind2;
    printf("\n\n\n\n\nDosyalarda bilgi var ise hepsi eklendi.\n\n");

//MENU 
    printf("YAPISAL PROGRAMLAMA DONEM PROJESI\n\n");
    printf("Bir ogrencinin alabilecegi maksimum ders sayisi:  ");
    scanf("%d",&maxcourse);                                                     
    printf("\nBir ogrencinin alabilecegi maksimum kredi:  ");
    scanf("%d",&maxcredit);

    printf("\n\nMENU\n\n\nDERS ISLEMLERI\n\n1-YENI DERS ACMA\n2-DERS KAPATMA\n\nOGRENCI ISLEMLERI\n\n3-OGRENCI EKLEME\n4-OGRENCI SILME\n5-OGRENCIYE DERS EKLEME\n6-OGRENCIDEN DERS SILME\n\nDERS PROGRAM ISLEMLERI\n\n7-DERSLERIN SINIF LISTESINI OLUSTURMA\n8-OGRENCININ DERS PROGRAMINI OLUSTURMA\n\n\n0-CIKIS\n\nIsleminizi giriniz:  ");
    scanf("%d",&secim);
    if(secim<=8 &&secim>=0) //secimlerin dogrulu kontrolu
    while(secim){
        if(secim<=8 &&secim>=0){
            switch (secim)
            {
            case 1://ders acma
                
                if(strcmp(iterl->course_name,"-1")){//ilk dugum bos degilse isi fonksiyonlara birakiyorum
                    yanlis=1;
                    while(yanlis){
                        printf("Acilacak dersin kodu:(ders kodlari 7 karakterli olmalidir): "); //ders kodu dogru girildi mi kontrolu 
                        scanf("%s",lsID);
                        if(strlen(lsID)==7){
                            yanlis=0;
                        }
                    }
                    yanlis=1; 
                    printf("Acilacak dersin adi: ");
                    scanf("%s",name);
                    printf("Acilacak dersin kredisi: ");
                    scanf("%d",&kredi);
                    printf("Acilacak dersin kapasitesi:  ");
                    scanf("%d",&kapasite);
                    open_course(iterl,lsID,name,kredi,kapasite,Is_lesson_exist,0,Dosyaya_Kaydet); //ders acma fonksiyonu
                }
                else{//ilk dugum bos ise islemi mainden yapiyoruz
                    yanlis=1;
                    while(yanlis){
                        printf("Acilacak dersin kodu:(ders kodlari 7 karakterli olmalidir): ");
                        scanf("%s",lsID);
                        if(strlen(lsID)==7){
                            yanlis=0;
                        }
                    }
                    yanlis=1;
                    printf("Acilacak dersin adi: ");
                    scanf("%s",name);
                    printf("Acilacak dersin kredisi: ");
                    scanf("%d",&kredi);
                    printf("Acilacak dersin kapasitesi:  ");
                    scanf("%d",&kapasite);


                    strcpy(iterl->course_name,lsID);
                    strcpy(iterl->fullname,name);
                    iterl->credit=kredi;
                    iterl->capasity=kapasite;
                    iterl->students=(long*)malloc(sizeof(long));                //ilk dugume eklendi
                    iterl->students[0]=-1;
                    iterl->next=NULL;
                    Dosyaya_Kaydet(iterl,iters,nodek);                         //dosyaya kaydedildi
                    printf("Ders olusturuldu.\n\n");
                }
                
                break;
            case 2://ders kapama
                    yanlis=1;
                    while(yanlis){
                        printf("Kapatilacak dersin kodu:(ders kodlari 7 karakterli olmalidir): ");
                        scanf("%s",lsID);
                        if(strlen(lsID)!=6){
                            yanlis=0;
                        }
                    }
                    yanlis=1;
                    close_course(iterl,lsID,Is_lesson_exist,0,Dosyaya_Kaydet,nodek,iters);  //ders kapama fonksiyonu

                break;
            case 3://ogrenci ekleme
                if(iters->student_no!=-1){//ilk dugum bos degil ise fonksiyon yapacak yine
                    yanlis=1;
                    while(yanlis){
                        printf("Eklenecek ogrencinin numarasi(Ogrenci numaralari 0'dan buyuk olmalidir): ");        //numara kontrolu
                        scanf("%ld",&numara);
                        if(numara>0){
                            yanlis=0;
                        }
                    }
                    
                    printf("Ogrencinin ismi: ");
                    scanf("%s",name);
                    printf("Ogrencinin soyismi: ");
                    scanf("%s",surname);
                    add_student(iters,numara,name,surname,Is_student_exist,0,0,0,Dosyaya_Kaydet);//ogrenci ekleme fonksiyonu
                }
                else{//ilk dugum bos ise elle eklemek zorundayim
                    yanlis=1;
                    while(yanlis){
                        printf("Eklenecek ogrencinin numarasi(Ogrenci numaralari 0'dan buyuk olmalidir): ");
                        scanf("%ld",&numara);
                        if(numara>0){
                            yanlis=0;
                        }
                    }
                    
                    printf("Ogrencinin ismi: ");
                    scanf("%s",name);
                    printf("Ogrencinin soyismi: ");
                    scanf("%s",surname);

                    iters->student_no=numara;
                    strcpy(iters->name,name);
                    strcpy(iters->surname,surname);
                    iters->total_credit=0;
                    iters->number_of_taken_course=0;                //Student ilk dugum ekleniyor
                    iters->prew=NULL;
                    iters->next=NULL;
                    Dosyaya_Kaydet(iterl,iters,iterk);              //Dosyaya kaydediliyor
                    printf("Ogrenci eklendi\n\n");
                }
                break;
            case 4://ogrenci silme
                

                printf("Silenecek ogrencinin numarasi: ");
                scanf("%ld",&numara);
                del_student(iters,numara,Is_student_exist,Dosyaya_Kaydet,nodek);        //ogreni silme programi



                break;
            case 5://ogrenciye ders ekleme  
                if(nodek->ID!=-1){//ilk dugum bos degilse fonksiyonlar
                    printf("Islem yapilacak ogrenci numarasi: ");
                    scanf("%ld",&numara);
                    i=Is_student_exist(iters,numara,index1);//ders eklenecek ogrencinin varligi kontrolu eger ogrenci varsa fonksiyondan 4,5ve 6 degeri donecek
                    if(i>3){
                        
                        printf("Kaydedilecegi dersID'si : ");
                        scanf("%s",lsID);
                        j=Is_lesson_exist(iterl,lsID,index2);   //ogrenciye eklenecek dersin varligi kontrolu ders vars fonksiyondan 4,5 veya 6 degeri donecek
                        if(j>3){
                            printf("Islemin tarihini giriniz: ");  //bu islem icin kullanicidan tarifte aliniyor
                            scanf("%s",date);
                            add_course(iters,iterl,numara,lsID,Is_lesson_exist,Is_student_exist,Dosyaya_Kaydet,nodek,0,date,maxcredit,maxcourse); //ogrenciye ders ekleme fonksiyonu

                        }
                        else{
                            printf("Bu ders ID'sine ait ders yok.\n\n");//ders yok
                        }
                    }
                    else{
                        printf("Bu numaraya ait ogrenci yok.\n\n"); //ogrenci yok 
                    }
                }
                else{//ilk dugum bos ise mainden
                    printf("Islem yapilacak ogrenci numarasi: ");
                    scanf("%ld",&numara);
                    i=Is_student_exist(iters,numara,index1);
                    if(i>3){
                        printf("Kaydedilecegi dersID'si : ");
                        scanf("%s",lsID);
                        j=Is_lesson_exist(iterl,lsID,index2);
                        if(j>3){
                            printf("Islemin tarihini giriniz: ");
                            scanf("%s",date);
                            if(i!=4){
                                for(i=0;i<ind1+1;i++){
                                    iters=iters->next;
                                }
                            }
                            
                            if(j!=4){
                                for(j=0;j<ind2+1;j++){                                                              //BURDA OGRENCIYE DERS EKLEME FONKSIYONUNDA YAPTIKLARIMI YAPIYORUM O FONKSIYONDA ACIKLAMALAR OLACAK
                                    iterl=iterl->next;
                                }
                            }
                            if(iters->total_credit+iterl->credit<=maxcredit){                   //dersi alirsa max krediyi veya max ders sayisini asar mi kontrolu  
                                if(iters->number_of_taken_course+1<=maxcourse){
                                    i=0;
                                    j=0;
                                    while(iterl->students[i]!=-1){
                                        if(iterl->students[i]<numara){
                                            j++;
                                        }
                                        i++;
                                    }
                                    if(iterl->students[j]!=numara){
                                        if(i < iterl->capasity){ //Ogrenci derse eklenirse dersin kapasitesi asilir mi kontrolu
                                            iterk->ID=1;
                                            strcpy(iterk->coursename,lsID);
                                            strcpy(iterk->situation,"KAYITLI");
                                            strcpy(iterk->date,date);
                                            iterk->next=NULL;
                                            iterk->student_no=numara;
                                            iters->number_of_taken_course+=1;                       //ilk dugum ayarlamalari
                                            iters->total_credit += iterl->credit;
                                            Dosyaya_Kaydet(les_node,stu_node,nodek);
                                            iters=stu_node;
                                            iterl=les_node;
                                            iterk=nodek;
                                            printf("Ogrenci derse kaydedildi.\n\n");
                                        }
                                        else{
                                            printf("Dersin kapasitesi dolu oldugundan islem gerceklestirilemedi.\n\n");
                                        }
                                        
                                    }
                                    else{
                                        printf("Ogrenci dersi zaten almis.\n\n");
                                    }
                                }
                                else{
                                    printf("Ogrenci alinabilecek maksimum ders sayisini astigindan dolayi islem yapilamadi.\n\n");
                                }
                            
                            }
                            else{
                                printf("Ogrenci maksimum krediyi astigindan dolayi islem yapilamadi.\n\n");
                            }
                            
                        }
                        else{
                            printf("Bu ders ID'sine ait ders yok.\n\n");
                        }
                    }
                    else{
                        printf("Bu numaraya ait ogrenci yok.\n\n");
                    }

                }

                
                break;
            case 6://ogrenciden ders silme
                printf("Islemin yapilacagi ogrenci numarasi: ");
                scanf("%ld",&numara);
                printf("Silenecek dersin Id'sini giriniz:  ");
                scanf("%s",lsID);
                printf("Islem tarihi:  ");
                scanf("%s",date);
                del_course(iterl,iters,numara,lsID,Is_lesson_exist,Is_student_exist,Dosyaya_Kaydet,0,date,iterk);
                break;
            case 7://derslerin ogrenci listesi
                AttendanceSheet(iterl);   //Her dersin ogrenci listesi dosyasi olusturma fonksiyon
                break;
            case 8://ogrencinin ders programi dosyasi 
                printf("Programini olusturmak istediginiz ogrencinin numarasini giriniz: ");
                scanf("%ld",&numara);

                if(Is_student_exist(iters,numara,index1)>3){//ogrenci varligi kontrolu
                    sprintf(name,"%ld",numara);//ogrenci numarasi stringe donusturulur cunku dosyayi olustururken lazimm olacak
                    StudentsSyllabus(iterk,name);//ogrencinin ders programi dosyasini olusturma fonksiyonu

                }
                else{
                    printf("Bu numaraya sahip ogrenci yok.\n\n");
                }
                break;
            }
        }
        printf("\n\nMENU\n\n\nDERS ISLEMLERI\n\n1-YENI DERS ACMA\n2-DERS KAPATMA\n\nOGRENCI ISLEMLERI\n\n3-OGRENCI EKLEME\n4-OGRENCI SILME\n5-OGRENCIYE DERS EKLEME\n6-OGRENCIDEN DERS SILME\n\nDERS PROGRAM ISLEMLERI\n\n7-DERSLERIN SINIF LISTESINI OLUSTURMA\n8-OGRENCININ DERS PROGRAMINI OLUSTURMA\n\n\n0-CIKIS\n\nIsleminizi giriniz:  ");
        scanf("%d",&secim);
    }
    printf("Program Kapatildi.\n");//program bittiginde bu mesaj verilir


    //OLUSTURULAN TUM DINAMIK BELLEKLER BU KISIMDA FREELENIR
    while(nodek->next!=NULL){   
        freek=nodek;
        nodek=nodek->next;
        free(freek);
    }

    freek=nodek;
    free(freek);

    long *free_students_in_course;
    while(les_node->next!=NULL){
        freel=les_node;
        free_students_in_course=freel->students;
        les_node=les_node->next;
        free(freel);
        free(free_students_in_course);
    }
    freel=les_node;
    free_students_in_course=freel->students;
    free(freel);
    free(free_students_in_course);

    while(stu_node->next!=NULL){
        frees=stu_node;
        stu_node->next->prew=NULL;
        stu_node=stu_node->next;
        free(frees);
    }
    frees=stu_node;
    free(frees);
    return 0;
}

//Bu fonksiyon dersin varlik kontrolunu ve ayni zamanda varsa nerede yoksa da sirali eklenebilmesi icin nerede olmali bilgisini return yapar
int Is_lesson_exist(Lesson *node,char new_course[leschr],int *index){//return 0=kayitli hic ders yok,1 = ders var, 2  ders yok ama en bastaki dugumden bile daha kuck degerili kodu, 3 ders yok node da ortalarda,4 ders yok ve  en sona eklenecek
    int i;
    *index=0;
    char tmp[leschr];
    if(!strcmp(node->course_name,"-1")){//dugum tamamen bos mu kontrolu

        return 0;
    }
    
/*
RETURN ANLAMLARI
0->ders dugumu tamamrn bos
1->ders yok ve en basa eklenmeli(eklenecekse)
2->ders yok ve ortaya eklenmeli                 bas sona veya ortaya eklenmesi linked list acisindan farklilik olusturdugu icin bu sekilde bir cozum buldum
3->ders yok ve en sona eklenmeli
4->ders var ve dugumun en basta
5->ders var ve dugumun ortalarinda              bas ,son veya ortadan ders silmekte linked list acisindan farklilik olsturur
6->ders var ve en sonda

Linked liste dersler sirali ekleniyor!!

Index degiskeni de deers kodunun hangi kacinci dugumde oldugunu veya kacinci dugumde olmasi gerektigi bilgisini saklar degeri kullanabilmek icin pointer olarak tanimliyorum
*/
    strcpy(tmp,node->course_name);
    i=strcmp(tmp,new_course);   //aranan ders ilk dugumde mi ?
    if(i==0){
        return 4;
    }
    else if(i>0){//dersin kodu en bastaki dugumden bile daha kucuk degerde 
        return 1;
    }

    while(node->next!=NULL){
        strcpy(tmp,node->next->course_name);
        i=strcmp(tmp,new_course);
        if(i==0){//ders bulundu
            if(node->next->next==NULL){//bulunan ders en sonda mi
                return 6;
            }

            return 5;//bulunan ders en sonda ve en basta degilse ortalardadir
        }
        else if(i>0){//ders bulunamadi ve artik aranan ders kodundan daha yuksek degerli dersler karsimiza cikiyorda ders yok ve ortaya konmalidir
            return 2;
        }
        node=node->next;//kod bulunamadi ise birdaha ki node aranir
        (*index)+=1;//her ders dugumu gecildiginde indexte artar
    }
    //eger buraya kadar gelindiyse linked listte dersle eslesen kod veya ders kodundan buyuk bir kod bulunmamakta
    return 3;//bu da ders kodunun en sona eklenmesi gerektigini gosterir
}
void open_course(Lesson *node,char course_name[leschr],char fullname[maxchar],int credit,int capasity,int (*Is_lesson_exist)(Lesson *node,char new_course[leschr],int *index),int isfromfile,void (*Dosyaya_Kaydet)(Lesson *lnode,Student *snode,Kayit *knode)){
    int *index;
    int ind=0,i;
    index=&ind;
    Lesson *tmpnode;//ders nodu uzerinde gezinecegimden head bilgisini saklamaliyim Dosyaya kaydederken gerekiyor
    tmpnode=node;

    int where = Is_lesson_exist(node,course_name,index); 
    
    if(where<4){//Ders varlik kontrolunden 4'tten kucuk bur deger gelmisse bu ders koduna ait ders bulunmadigini gosterir
        Lesson *tmp;
        tmp = (Lesson *)malloc(sizeof(Lesson)); //eklenecek dugum olusturulur
        switch (where)
        {
            case 0://dugum tamamen bos

                strcpy(tmp->course_name,course_name);
                strcpy(tmp->fullname,fullname);
                tmp->credit=credit;
                tmp->capasity=capasity;
                tmp->students=(long *)malloc(sizeof(long));//ogrenciler icin dinamik bellek olusturulur
                tmp->students[0]=-1;//ve ilk eleman -1'e esitlenir boylece bos oldugunu anliyorum
                node=tmp;
                node->next=NULL;
                break;
            case 1://basa ekleniyor
                strcpy(tmp->course_name,node->course_name);
                strcpy(tmp->fullname,node->fullname);
                tmp->credit=node->credit;
                tmp->capasity=node->capasity;
                tmp->next=node->next;
                tmp->students=node->students;
                strcpy(node->course_name,course_name);              //enbasa direk ekleyemedigimden head'in tum degerlerini yeni node'a ekliyorum ve head'e istenilen dersi yerlestiriyorum ve headin yeni nodeu isaretlemesini sagliyorum
                strcpy(node->fullname,fullname);
                node->credit=credit;
                node->capasity=capasity;
                node->next=tmp;
                node->students=(long*)malloc(sizeof(long));
                node->students[0]=-1;
                break;
            
            case 2://ortalara ekleniyor
                for(i=0;i<ind;i++){
                    node=node->next;      //ind degeri dersin kacinci dugumde oldugu veya olmasi gerektigini gosterir, istenilen dugume kadar dugumde geziyorum
                }
                strcpy(tmp->course_name,course_name);
                strcpy(tmp->fullname,fullname);                 //yeni dugume ders degerlerimi yerlestirip dugumde olmasi gerektigi yere sirali eklemsis oluyorum
                tmp->credit=credit;
                tmp->capasity=capasity;
                tmp->next=node->next;
                node->next=tmp;
                tmp->students=(long *)malloc(sizeof(long));
                tmp->students[0]=-1;

                break;
            case 3://sona ekleniyor
                for(i=0;i<ind;i++){
                    node=node->next;
                }
                strcpy(tmp->course_name,course_name);
                strcpy(tmp->fullname,fullname);
                tmp->capasity=capasity;
                tmp->credit=credit;
                tmp->next=NULL;                                 //en sona ekliyorum
                node->next=tmp;
                tmp->students=(long*)malloc (sizeof(long));
                tmp->students[0]=-1;
                break;
        }

        if(isfromfile!=1){  //Eger Geleen ders zaten dosyadan dugumlere eklemek icin geliyorsa dosyalarda bir degisiklik yapmiyorum
            Student *rr;
            rr=(Student *)malloc(sizeof(Student));
            rr->student_no=0;//Dosyaya kaydet fonksiyonu bu degeri gorunce ogrenciler dosyasinda degisiklik yapmayacak
            Kayit *pp;
            pp=(Kayit*)malloc(sizeof(Kayit));
            pp->ID=0;//Kayit dugumu nde de bu degeri gorunce Ders Kayit dosyasinda degisiklik yapmayacak
            Dosyaya_Kaydet(tmpnode,rr,pp);//bu sekilde degisiklik yapacagi tek Dosya dersler dosyasi olur
            free(rr);
            free(pp);//deger gondermek icin olusturdugum alanlari siliyorum
        }
        printf("Ders Olusturuldu.\n\n");
    }
    else{
        printf("Ders zaten olusturulmus!\n\n");
    }
    
}
void close_course(Lesson *node,char course_name[leschr],int (*Is_lesson_exist)(Lesson *node,char new_course[leschr],int *index),int isfromfile,void (*Dosyaya_Kaydet)(Lesson *lnode,Student *snode,Kayit *knode),Kayit *knode,Student *snode){
    int ind,i,cre;
    int *index;
    index=&ind;
    int where=Is_lesson_exist(node,course_name,index);
    Lesson *tmpnode;
    tmpnode=node;//ders nodunun uzerinde gezinecegim icin headi sakliyorum cunku Dosyaya kaydete gonderecegim
    if(where>3){//Ders varligi kontrolunde ders var gorunuyorsa dersi siler
        switch (where) {
            case 4://silinecek ders en basta
                if(node->next==NULL){//en bastan silinecek ama baska node yok
                    strcpy(node->course_name,"-1");
                    free(node->students);
                    node->students=(long*)malloc(sizeof(long));
                    node->students[0]=-1;
                    cre=node->credit;               //eger tek dugum varsa ve o silinecekse sadece o dugumu temizliyorum
                    node->capasity=0;
                    node->credit=0;
                    strcpy(node->fullname,"-");//boyle oldugunde dosyada degisiklik olsun

                    
                }
                else{//enbastaki node silinecek ama diger dugumler mevcut
                    Lesson *del;//silinecek dugumu isaretleyecek                                    //ILK DUGUMU DIREK SILEMEYECEGIMDENILK DUGUME ONDAN SONRAKI DUGUMUND EGERLERINI YERLESTIRIP 2. DUGUMU SILIYORUM
                    strcpy(node->course_name,node->next->course_name);
                    strcpy(node->fullname,node->next->fullname);
                    cre=node->credit;//silinecek dersin kredisini aldim en basta
                    node->capasity=node->next->capasity;
                    node->credit=node->next->credit;
                    del=node->next;
                    node->next=node->next->next;
                    free(del);//SILINECEK ALAN FREELENDI
                }
                break;
            Lesson *del;//burdan sonra kesin bir node silineceginden burda tanimladim
            case 5://ortalarda
                
                for(i=0;i<ind;i++){// ind degeri Dersin varlik kontrolunden donen index degeri 
                    node=node->next;//silinecek dugumden bir oncekine gidiyoruz
                }
                cre=node->next->credit;
                del=node->next;                         //ortalardan siliniyor
                node->next=node->next->next;
                free(del);
                break;
            case 6://en sonda
               
                for(i=0;i<ind;i++){
                    node=node->next;
                }
                cre=node->next->credit;     
                del=node->next;             //en sondan silindi
                node->next=NULL;
                free(del);
                break;

        } 
        if(!isfromfile){//Zaten bu bilgiler dosyadan geliyorsa dosya da degisiklik yapmmaz

            //kayit dosyasinda tum bu ders idsine sahip olanlari DERS KAPANDI demek lazim
            //eskiden bu derse sahip tum ogrencilerin toplam ders sayisi ve toplam kredisi degisecek
            char kapandi[]="DERS_KAPANDI",kayitli[]="KAYITLI",birakti[]="BIRAKTI";
            long stuid;

            Student *ttmpnode;
            ttmpnode=snode;             //iki dugumunde uzerinde gezinecegimden headi tutan degiskeni tanimliyorum
            Kayit *tttmpnode;
            tttmpnode=knode;

            while(knode->next!=NULL){
                if(!strcmp(knode->coursename,course_name)){//kayit dosyasinda ayni ders idsine ait tum degerleri buluyorum

                    snode=ttmpnode;//basa donduruyorum
                    //eger bulunan dugumde durum BIRAKTI  ise bir degisiklik yapmiyorum
                    if(!strcmp(knode->situation,kayitli)){//yapilan islem KAYITLI mi diye kontrol ediyorum cunku ogrenciler dosyasini duzenleyecegim
                        stuid=knode->student_no;
                        while(snode->student_no<stuid){
                            snode=snode->next;
                        }
                        if(snode->student_no==stuid){
                            snode->number_of_taken_course-=1;//bu dersi alan tum ogrencilerin alinan derslerini bi azaltip kredilerini duzenledim
                            snode->total_credit-=cre;
                        }
                        strcpy(knode->situation,kapandi);//daha sonra dersleri ders kapandi diye ayarladim
                
                    }

                }
                
                knode=knode->next;
            }      
            if(!strcmp(knode->coursename,course_name)){//son dugum kontrolu
                snode=ttmpnode;
                if(!strcmp(knode->situation,kayitli)){
                    stuid=knode->student_no;
                    while(snode->student_no<stuid){
                        snode=snode->next;
                    }
                    if(snode->student_no==stuid){
                        snode->number_of_taken_course-=1;
                        snode->total_credit-=cre;
                    }
                }
                strcpy(knode->situation,kapandi);
            }
            
            Dosyaya_Kaydet(tmpnode,ttmpnode,tttmpnode);   //Dosyaya kaydetmek icin dugumlerin headini gonderiyorum
        }  
        
        printf("Ders Kapatildi.\n\n");

    }
    else{
        printf("%s ID'sine ait ders bulunmamakta.\n\n",course_name);
    }
}
int Is_student_exist(Student *node,long Number,int *index){
    int i;
    *index=0;


    /*
    RETURN ANLAMLARI (mantik ders varligi kontroluyle ayni)
    0->Dugum tamamen bos
    1->ogrenci yok ama en basa konmali
    2->ogrenci yok ortaya konmali
    3->ogrenci yok sona konmali
    4->ogrenci var ve en basta
    5->ogrenci var ve ortalarda
    6->ogrenci var ve en sonda
    
    index degeri de ogrencinin hangi dugumde oldugunu veya konmasi gerektigini gosterir
    */
    if(node->student_no==-1){//dugum bos
        return 0;
    }
    if(node->student_no==Number){
        return 4;//var en bas
    

    }
    else if(node->student_no>Number){
        return 1;//ogrenci yok ama en basa konmali
    }
    while(node->next!=NULL){
        
        if(node->next->student_no==Number){
            if(node->next->next==NULL){
                return 6;//var en sonda
            }
            return 5;//var ortada
        }
        else if(node->next->student_no>Number){
            return 2;//yok ortaya konulacak
        }
        node=node->next;
        (*index)++;
    }
    return 3;//yok sona konulacak
}


void add_student(Student *node,long no,char name[maxchar],char surname[maxchar],int (*Is_student_exist)(Student *node,long Number,int *index),int credit,int number_of_takencourse,int isfromfile,void (*Dosyaya_Kaydet)(Lesson *lnode,Student *snode,Kayit *knode)){//OGRENCI YENI EKLENDIGI ICIN KREDISI VE DERSLERINI AYRI BIR SEKILDE ALDIM
    int ind,i;   
    int *index=&ind;
    int where=Is_student_exist(node,no,index);//ogrenci varligi kontrolu
    Student *tmpnode;
    tmpnode=node;
    if(where<4){//ogrenci yok ise islem yapilir
        Student *new;
        new=(Student *)malloc(sizeof(Student));//eklenecek yeni node un alani
        switch (where)
        {
        case 1://node en basa konmali ,ilk head dugumundeki degerler yeni dugume atanir headin degerleri basa konulmak istenen degerlerle degistirilir ve headin yeni nodu gostermesi saglanir
            
            new->student_no=node->student_no;
            strcpy(new->name,node->name);
            strcpy(new->surname,node->surname);
            new->number_of_taken_course=node->number_of_taken_course;           //yeni dugume headin degerleri aktariliyor
            new->total_credit=node->total_credit;
            new->next=node->next;
            new->prew=node;
            if(node->next==NULL){//sadece tek dugum varsa ona gore islem
                new->next=NULL;
                new->prew=node;
            }
            else{
                node->next->prew=new;
            }
            
            node->student_no=no;
            strcpy(node->name,name);
            strcpy(node->surname,surname);
            node->number_of_taken_course=number_of_takencourse;  //basa konacak degerler heade yerlestirilir
            node->total_credit=credit;
            node->next=new;
        break;
        
        case 2://nodeun ortalara eklenmesi durumu
            for(i=0;i<ind;i++){
                node=node->next;        //eklenmesi gerekn dugum yerinden bir onceki dugume gelinir
            }
            new->student_no=no;
            strcpy(new->name,name);
            strcpy(new->surname,surname);
            new->number_of_taken_course=number_of_takencourse;
            new->total_credit=credit;
            new->next=node->next;                       //yeni dugume degerler eklenir
            new->prew=node;             
            node->next->prew=new;
            node->next=new;                             //yeni dugum eklenir
            

            break;
        case 3://dugumun en sona eklenmesi durumu
            for(i=0;i<ind;i++){
                node=node->next;        //en son degere gelinir
            }
            new->student_no=no;
            strcpy(new->name,name);
            strcpy(new->surname,surname);
            new->number_of_taken_course=number_of_takencourse;
            new->total_credit=credit;           //yeni olusturuluan alana degerler aktarilir yine
            new->next=NULL;//sonuna Null deeri verilir
            new->prew=node;
            node->next=new;     //ve linked liste eklenir
            break;

        }
        printf("Ogrenci eklendi\n\n");
        if(!isfromfile){//islem dosyadan geliyorsa dosyalarda degisiklik yapilmaz
            Lesson *r;
            r = (Lesson *)malloc(sizeof(Lesson));
            Kayit *pp;
            pp=(Kayit*)malloc(sizeof(Kayit));
            pp->ID=0;//kayit dosyasinda degisiklik olmasin diye bu deger gonderilir
            strcpy(r->course_name,"yapma");//ders dosyasinda degisiklik olmasin diye bu deger gonderilir
            Dosyaya_Kaydet(r,tmpnode,pp);//bu sekilde sadece ogrenci dosyasinda degisim gerceklesecek
            free(r);
            free(pp);
        }
        
    }
    else{
        printf("Ogrenci zaten ekli!\n\n");
    }

}

void del_student(Student *node,long no,int (*Is_student_exist)(Student *node,long Number,int *index),void (*Dosyaya_Kaydet)(Lesson *lnode,Student *snode,Kayit *knode),Kayit *knode){
    int ind,i,where;
    int *index;
    index= &ind;
    Student *tmpnode;
    tmpnode=node;//yine headin tutan deger eklenir
    int dersaldi;
    where=Is_student_exist(node,no,index);//ogrenci varlik kontrolu
    if(where>3){//ogrenci var ise islem yaplir
        switch (where)
        {
        case 4://ogrenci var ve en basta
            if(node->next==NULL){//eger zatem tek node varsa sadece node daki degerler silinir
                dersaldi=node->number_of_taken_course;
                node->student_no=-1;
                node->number_of_taken_course=0;
                node->total_credit=0;
                strcpy(node->name,"");
                strcpy(node->surname,"");

            }
            else{//tek node yoksa
                Student *del;//silinecek alani pointleyen degisken
                strcpy(node->name,node->next->name);
                strcpy(node->surname,node->next->surname);              //ilk dugumdeki degerler ondan sonrakiyle degistirilir ve ikinci dugum silinir
                dersaldi=node->number_of_taken_course;
                node->student_no=node->next->student_no;
                node->number_of_taken_course=node->next->number_of_taken_course;
                node->total_credit=node->next->total_credit;
                del= node->next;
                if(node->next->next!=NULL){
                    node->next->next->prew=node;
                    node->next=node->next->next;
                }
                else{
                    node->next=NULL;
                }

                free(del);
            }
            break;
        Student *del;//burdan sonra her turlu bir alan silineceginden 
        case 5://ortalardan silinmesi
            for(i=0;i<ind;i++){     //index sayesinde silinecek ogrencinin linked listin neresinde oldugunu bulabiliyoruz
                node=node->next;
            }
            del=node->next;
            dersaldi=node->next->number_of_taken_course;//hic ders almismiydi kontrolu dosyaya kaydderken isimize yarayacak
            node->next->next->prew=node;
            node->next=node->next->next;
            free(del);
            break;
        
        case 6://en sondan silinmesi
            for(i=0;i<ind;i++){
                node=node->next;
            }   
            dersaldi=node->next->number_of_taken_course;
            del=node->next;
            node->next=NULL;
            free(del);

        }

        
        //dosyaya kaydetme islemi
        Lesson *r;
        r=(Lesson *)malloc(sizeof(Lesson));
        strcpy(r->course_name,"yapma");//ders dosyasinda degisiklik yapilmasin

        if(dersaldi){//ders aldiysa aldigi derslere BIRAKTI durumu gelmesi lazim
            char kapandi[]="DERS_KAPANDI",birakti[]="BIRAKTI",kayitli[]="KAYITLI";
            Kayit *ttmpnode;
            ttmpnode=knode;//head tutar
            while(knode->next!=NULL){
                if(knode->student_no==no&&!strcmp(knode->situation,kayitli)){//ogrenci varsa ve durum kayitli ise durum BIRAKTI olarak degistirilir
                    strcpy(knode->situation,birakti);
                }
                knode=knode->next;
            }
            if(knode->student_no==no&&!strcmp(knode->situation,kayitli)){//son deger kontrolu
                strcpy(knode->situation,birakti);
            }
            
            Dosyaya_Kaydet(r,tmpnode,ttmpnode);//kayit ve ogrenci dosyasinda degisiklik yapilacak

        }
        else{//hi ders almadiysa kayit dosyasinde bir degisiklik yapilmasina gererk yok
            Kayit *ttmpnode;
            ttmpnode=(Kayit *)malloc(sizeof(Kayit));
            ttmpnode->ID=0;//kayit dosyasinda degisiklik olmasin
            Dosyaya_Kaydet(r,tmpnode,ttmpnode);//sadece ogrenci dosyasinda degisiklik yapilacak
            free(ttmpnode);
        }
        printf("Ogrenci silindi");

        free(r);
        

    }
    else{
        printf("Bu numaraya ait ogrenci yok!\n\n");
    }
}


int add_course(Student *snode,Lesson *lnode,long student_no,char course_name[leschr],int (*Is_lesson_exist)(Lesson *node,char new_course[leschr],int *indexl),int (*Is_student_exist)(Student *node,long Number,int *indexs),void (*Dosyaya_Kaydet)(Lesson *lnode,Student *snode,Kayit *knode),Kayit *knode,int isfromfile,char date[maxchar],int maxcredit,int maxtakencourse){
    int course_exist,student_exist,cind,sind,*course_index,*student_index,i,j,tmp,tmp2;
    course_index=&cind;
    student_index=&sind;
    Student *tmps;
    tmps=snode;
    Lesson *ttmp;
    ttmp=lnode;
    Kayit *tttmp;
    tttmp=knode;



    course_exist=Is_lesson_exist(lnode,course_name,course_index);
    student_exist=Is_student_exist(snode,student_no,student_index);
    if(course_exist>3 && student_exist>3){//dersin ve ogrencinin varligi kontrolu
        if(student_exist!=4){
            for(i=0;i<sind+1;i++){
                snode=snode->next;//ogrencinin oldugu dugume getirir
            }                                                                                   //her ikisi icinde 4 return olmussa zaten dugumun en basinda
        }
        

        if (course_exist!=4){
            for(i=0;i<cind+1;i++){
                lnode=lnode->next;//dersin oldugu dugumdeyiz
            }
        }
        if((snode->total_credit+lnode->credit)>maxcredit){//dersi alirsa max krediyi asiyor mu kontrolu
            printf("Ogrenci maksimum krediyi astigindan dolayi islem yapilamadi.\n\n");
            return 0;
        }
        if((snode->number_of_taken_course+1)>maxtakencourse){//dersi alirsa max alinabilecek ders sayisini asiyor mu kontrolu
            printf("Ogrenci alinabilecek maksimum ders sayisini astigindan dolayi islem yapilamadi.\n\n");
            return 0;
        }

        
        i=0;
        j=0;
        
        while(lnode->students[i]!=-1){//-1'e gelindiginde derse kayitli ogrencilerin hepsini gezmis olur
            if(lnode->students[i]<student_no){//dugumdeki ogr numaralari sirali olugunden ogrencinin nereye eklenecegi bilgisini tutar
                j++;//ogrencinin konulacagi indis
            }
            i++;//dersteki tumogrencilerin sayisi
        }
        
        

        if(lnode->students[j]==student_no){//eger ogrenci almissa
            printf("Ogrenci dersi zaten almis.\n\n");
           return 0;
        }
            
        if(lnode->capasity > i){//ders kapasitesi dolmamissa
            i++;    //-1'i de ekliyorum                                   
            tmp=lnode->students[j];


            lnode->students=(long *)realloc(lnode->students,(i+1)*sizeof(long));//yeni ogrenci ekleneceginden alan acilir

            for(;j<i;j++){
                lnode->students[j]=student_no;            
                tmp2=lnode->students[j+1];          //ogrnci konmasi gereken yere konur
                student_no=tmp;
                tmp=tmp2;
            }

            lnode->students[i]=-1;//sona -1


        
            
            if(!isfromfile){//odosyadaki bilgiler okunmuyorsa dosyalarda degisiklik yapilacak
                snode->number_of_taken_course+=1;
                snode->total_credit+=lnode->credit;//ogrencinin toplam dersi ve toplam kredisi duzenlenir


                while(knode->next!=NULL){
                    knode=knode->next;
                }

                Kayit *new;
                new=(Kayit*)malloc(sizeof(Kayit));//yeni kayit
                new->ID=((knode->ID)+1);
                strcpy(new->date,date);
                strcpy(new->situation,"KAYITLI");
                strcpy(new->coursename,course_name);
                new->student_no=snode->student_no;
                new->next=NULL;
                knode->next=new;

                Dosyaya_Kaydet(ttmp,tmps,tttmp);//Tum dosyalar duzenlenir
                printf("Ogrenci derse kaydedildi.\n\n");
            }
            return 1;
        }
        else{
            printf("Dersin kapasitesi dolu oldugundan islem gerceklestirilemedi.\n\n");
            return 0;
        }
        


        
    }
    else{
        printf("Dersi kodunu veya ogrenci numarasini yanlis yazdiginizdan islem gerceklestirilemedi.\n\n");
        return 0;
    }

    
}
int del_course(Lesson *lnode,Student *snode,long stID,char lsID[leschr],int (*Is_lesson_exist)(Lesson *node,char new_course[leschr],int *indexl),int (*Is_student_exist)(Student *node,long Number,int *indexs),void (*Dosyaya_Kaydet)(Lesson *lnode,Student *snode,Kayit *knode),int isfromfile,char date[maxchar],Kayit *knode){


    int course_exist,student_exist,sind,lind,*student_index,*lesson_index,i,j,tmp;
    student_index=&sind;
    lesson_index=&lind;
    course_exist=Is_lesson_exist(lnode,lsID,lesson_index);
    student_exist=Is_student_exist(snode,stID,student_index);

    Kayit *tmpk;
    tmpk=knode;

    Student *tmps;
    tmps=snode;

    Lesson *tmpl;
    tmpl=lnode;
    if(course_exist>3 && student_exist>3){//dersin ve ogrencinin varligi kontrolu
        if(student_exist!=4){
            sind+=1;//BIZIM UZERINDE DEGISIKLIK YPACAGIMIZ OGRENCI NODUNUN INDEXI
            for(i=0;i<sind;i++){
                
                snode=snode->next;//ogrencinin oldugu dugumdeyiz
                
            }                                                                                   //4 return olmussa zaten dugumun en basinda
        }
        if (course_exist!=4){
            lind+=1;
            for(i=0;i<lind;i++){
                lnode=lnode->next;//dersin oldugu dugumdeyiz
                
            }
        }
        
        
        i=0;
        j=0;

        while(lnode->students[i]!=-1){
            if(lnode->students[i]<stID){        //ogrencininoldugu dugume geliyoruz
                j++;//ogrencinin oldugu dugum
            }
            i++;//tumogrencilerin sayisi
        }
        
        if(lnode->students[j]==stID){//eger ogrenci varsa
            tmp=lnode->students[j+1];
            for(;j<i+1;j++){            
                lnode->students[j]=tmp;     //derse kayitli ogrencilerden ogrenci silinir
                tmp=lnode->students[j+2];
            }

            if(!isfromfile){
                char kayitli[]="KAYITLI",birakti[]="BIRAKTI";
                snode->number_of_taken_course--;  //ogrenci dugumlerinden toplam ders ve kredi duzenlnir
                snode->total_credit-=lnode->credit;
                while(knode->student_no !=stID ||  strcmp(knode->coursename,lsID)){//Ogrencinin derse kaydoldugu satiri bulur kayit dugumunde
                    knode=knode->next;
                }
                if(!strcmp(knode->situation,kayitli)){//ders kapandiysa degistirmez
                    strcpy(knode->situation,birakti);//kayitli gorunuyorsa BIRAKTI diye degistirilir
                    strcpy(knode->date,date);
                }
                Dosyaya_Kaydet(tmpl,tmps,tmpk);//tum degisiklikler dosyaya kaydedilir


            }

           return 1;
        }
        else{
            printf("Ogrenci bu dersi almiyor.\n\n");
            return 0;
        }
       
    }
    else{
        printf("Ogrenci numarasi veya Ders kodu yok.\n\n");
        return 0;
    }
}
void AttendanceSheet(Lesson *lnode){
    int i,j=0;
    char lsfile[maxchar],txt[]=".txt";

    if(strcmp(lnode->course_name,"-1")){//hic ders yoksa islem yapmaz sadece mesaj verir
        
        while(lnode->next!=NULL){//islem tum dosyalar icin tekrarlar
            i=1;
            j=0;
            strcpy(lsfile,lnode->course_name);
            strcat(lsfile,txt);
            FILE *ders=fopen(lsfile,"w");//dersin koduyla yeni dosya olusturulur
            fprintf(ders, "%s dersinin sinif listesi\n\n",lnode->course_name);
            while(lnode->students[j]!=-1){
                fprintf(ders," %d -  %ld\n",i,lnode->students[j]);//tum ogrenciler sirali dosyaya yazdirilir
                j++;
                i++;
            }
            fclose(ders);
            
            lnode=lnode->next;
        }


        strcpy(lsfile,lnode->course_name);//son dosya icinde ayni islem
        strcat(lsfile,txt);
        FILE *ders=fopen(lsfile,"w");
        j=0;
        i=1;
        fprintf(ders, "%s dersinin sinif listesi\n\n",lnode->course_name);
        while(lnode->students[j]!=-1){
            fprintf(ders," %d_  %ld\n",i,lnode->students[j]);   
            i++;                       //sonuncuyu burda yapiyorum
            j++;
        }
        fclose(ders);
        lnode=lnode->next;


    }
    else{
        printf("Ogrenci listesi dosyalanacak ders bulunmamakta.\n\n");
    }

    
}

void FileBegginning(int isempty[3]){
    FILE *dersfr=fopen("Dersler.txt","r");
    char tmpc[55];
    long tmp;
    char first[55];
    if(dersfr==NULL){//okunacak dersler dosyasi acilmadiysa olusturulur
        fclose(dersfr);
        FILE *dersfw = fopen("Dersler.txt","w"); //dosya hali hazirda yoksa olusturuldu
        fprintf(dersfw,"%s,%s,%s,%s\n","DERSID","DERS_ADI","KREDI","KONTENJAN");  //dosya yeni acildigi icin bunlari da yazdiriyoruz

        fclose(dersfw);
        isempty[0]=1;//ici bos oldugu bilgisi gonderildi

    }
    else{//dosya var ise
        fseek(dersfr,0,SEEK_END);
        if(ftell(dersfr)==0){//dosyanin ici tamamen bos ise basliklar yazdirilmali
            
            FILE *dersfw = fopen("Dersler.txt","w");//dosya yeniden acildi 
            fprintf(dersfw,"%s,%s,%s,%s\n","DERSID","DERS_ADI","KREDI","KONTENJAN");
            fclose(dersfw);
        }
        fseek(dersfr,0,SEEK_SET);
        fscanf(dersfr,"%[^,],%[^,],%[^,],%[^\n]\n",tmpc,tmpc,tmpc,tmpc);
        tmp=ftell(dersfr);
        fseek(dersfr,0,SEEK_END);
        
        if(ftell(dersfr)==tmp){
            isempty[0]=1;//ici bos
        }
        else{//eger dosya icinde baslik disinda bir sey varsa ici dolu bilgisi tutulur
            isempty[0]=0;//ici bos degil
        }
        
        

    }
    fclose(dersfr);


    FILE *ogrfr=fopen("Ogrenciler.txt","r");
    char first2[55];
    if(ogrfr==NULL){
        fclose(ogrfr);
        FILE *ogrfw = fopen("Ogrenciler.txt","w"); //dosya hali hazirda yoksa olusturuldu
        fprintf(ogrfw,"%s,%s,%s,%s,%s\n","OGRENCI_NUMARASI","AD","SOYAD","TOPLAM_DERS","TOPLAM_KREDI");  //dosya yeni acildigi icin bunlari da yazdiriyoruz

        fclose(ogrfw);
        FILE *ogrfr=fopen("Ogrenciler.txt","r");
        isempty[1]=1;
    }
    else{
        fseek(ogrfr,0,SEEK_END);//AMA BOS MU?
        
        if(ftell(ogrfr)==0){//dosya olusmus ama ici tamamen bossa ilk basta basliklari ekliyorum
            FILE *ogrfw = fopen("Ogrenciler.txt","w");
            fprintf(ogrfw,"%s,%s,%s,%s,%s\n","OGRENCI_NUMARASI","AD ","SOYAD","TOPLAM_DERS","TOPLAM_KREDI");
            fclose(ogrfw);
        }

        fseek(ogrfr,0,SEEK_SET);
        fscanf(ogrfr,"%[^,],%[^,],%[^,],%[^,],%[^\n]\n",tmpc,tmpc,tmpc,tmpc,tmpc);

        tmp=ftell(ogrfr);
        fseek(ogrfr,0,SEEK_END);

        
        if(ftell(ogrfr)==tmp){
            isempty[1]=1;
        }
        else{
            isempty[1]=0;
        }

    }
    fclose(ogrfr);

    FILE *kytfr=fopen("OgrenciDersKayit.txt","r");
    char first3[55];
    if(kytfr==NULL){
        fclose(kytfr);
        FILE *kytfw = fopen("OgrenciDersKayit.txt","w"); //dosya hali hazirda yoksa olusturuldu
        fprintf(kytfw,"%s,%s,%s,%s,%s\n","ID","DERS_KODU","OGRENCI_NO","TARIH","DURUM");  //dosya yeni acildigi icin bunlari da yazdiriyoruz

        fclose(kytfw);
        FILE *kytfr=fopen("OgrenciDersKayit.txt","r");
        isempty[2]=1;

    }
    else{
        //AMA BOS MU?
        fseek(kytfr,0,SEEK_END);
        if(ftell(kytfr)==0){//dosya olusmus ama ici tamamen bossa ilk basta basliklari ekliyorum
            fclose(kytfr);
            FILE *kytfw = fopen("OgrenciDersKayit.txt","w");
            fprintf(kytfw,"%s,%s,%s,%s,%s\n","ID","DERS_KODU","OGRENCI_NO","TARIH","DURUM");
            fclose(kytfw);
            FILE *kytfr=fopen("OgrenciDersKayit.txt","r");

        }
        fseek(kytfr,0,SEEK_SET);

        fscanf(kytfr,"%[^,],%[^,],%[^,],%[^,],%[^\n]\n",tmpc,tmpc,tmpc,tmpc,tmpc);

        tmp=ftell(kytfr);
        fseek(kytfr,0,SEEK_END);
        
        if(ftell(kytfr)==tmp){
            isempty[2]=1;
        }
        else{
            isempty[2]=0;
        }


    }
    fclose(kytfr);

}

void Dosyaya_Kaydet(Lesson *lnode,Student *snode,Kayit *knode){
    
    
    if(strcmp(lnode->course_name,"yapma")){//eger bu course_name ile gondeilmisse dersler dosyasinda degisiklk istenmiyordur
        FILE *dersfw;
        dersfw=fopen("Dersler.txt","w");//degisiklik istenmsse dosya bosaltilip yazma modunda acilir
        fprintf(dersfw,"%s,%s,%s,%s\n","DERS_ID","DERS_ADI","KREDI","KONTENJAN");//basliklar
        while(lnode->next!=NULL){//son degere kadar ders dugumundeki degerler dosyaya uygun formatta yazdirilir
            fprintf(dersfw,"%s,%s,%d,%d\n",lnode->course_name,lnode->fullname,lnode->credit,lnode->capasity);
            lnode=lnode->next;
        }
        if(strcmp(lnode->course_name,"-1")){//dugumun tamamen bos olmasi durumunda hicbir sey yazdirmaz
            fprintf(dersfw,"%s,%s,%d,%d\n",lnode->course_name,lnode->fullname,lnode->credit,lnode->capasity);//son dugum yazdirilir
        }
    
        fclose(dersfw);
    }
    //diger dosyalarda da ayni mantikla dugumdeki degerler dosyada istenilen formatta yazilir
    if(snode->student_no!=0){//eger bu ogrenci numarasiyla gonderilmisse ogrenciler dosyasinda degisiklik istenmiyordur
        FILE *ogrfw;
        ogrfw=fopen("Ogrenciler.txt","w");
        fprintf(ogrfw,"%s,%s,%s,%s,%s\n","OGRENCI_NUMARASI","AD","SOYAD","TOPLAM_DERS","TOPLAM_KREDI");
        while(snode->next!=NULL){
            fprintf(ogrfw,"%ld,%s,%s,%d,%d\n",snode->student_no,snode->name,snode->surname,snode->number_of_taken_course,snode->total_credit);          
            snode=snode->next;
        }
        if(snode->student_no!=-1){
            fprintf(ogrfw,"%ld,%s,%s,%d,%d\n",snode->student_no,snode->name,snode->surname,snode->number_of_taken_course,snode->total_credit);//tum ogrenciler silinmisse
        }

        fclose(ogrfw);
    }
    if(knode->ID!=0){//eger bu ID ile gonderilmisse kayit dosyasinda degisiklik istenmiyordur
        FILE *kytfw;
        kytfw =fopen("OgrenciDersKayit.txt","w");
        fprintf(kytfw,"%s,%s,%s,%s,%s\n","ID","DERS_KODU","OGRENCI_NO","TARIH","DURUM");
        while(knode->next!=NULL){
            fprintf(kytfw,"%d,%s,%ld,%s,%s\n",knode->ID,knode->coursename,knode->student_no,knode->date,knode->situation);
            knode=knode->next;
        }
        if(knode->ID!=-1){
            fprintf(kytfw,"%d,%s,%ld,%s,%s\n",knode->ID,knode->coursename,knode->student_no,knode->date,knode->situation);
        }
        fclose(kytfw);
    }

}
void StudentsSyllabus(Kayit *knode,char no_char[maxchar]){//ogrencinin ders programini olusturma
    char kayitli[]="KAYITLI",txt[]=".txt";
    long no=atoi(no_char);//char olarak gelen ogrenci numarasinin int hali de saklanir
    FILE *dersprogrami;
    strcat(no_char,txt);//dosya ismi ayarlanir
    dersprogrami=fopen(no_char,"w");//dosya olusturulur
    fprintf(dersprogrami,"%ld NUMARALI OGRENCININ DERS PROGRAMI\n\n",no);
    if(knode->ID!=-1){//kayit nodeu bos ise hic bir kayit olusturulmamistir bu durumda ogrencinin ders programi bos gorunur
        
        while(knode->next!=NULL){

            if(knode->student_no==no   &&  !strcmp(knode->situation,kayitli)){//ogrencinin kayitli oldugu dersleri buluyorum
                fprintf(dersprogrami,"    %s    \n",knode->coursename);//bulunan her ders yazdirilir

            }
            knode=knode->next;
        }
        //son dugum
        if(knode->student_no==no   &&  !strcmp(knode->situation,kayitli)){
            fprintf(dersprogrami,"    %s    \n",knode->coursename);
        }

    }
    fclose(dersprogrami);


}
