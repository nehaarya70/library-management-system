#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<stdio.h>
#include<string.h>
#include<process.h>
#include<iomanip.h>
class book
{
 public:
    int bkid;
    char bnm[100];
    char atnm[100];
    float price;
    int status,rtrn;
    void acptbk()
    {
	cout<<"\nEnter book ID:";
	cin>>bkid;
	cout<<"Enter Book Name:";
	gets(bnm);
	cout<<"Enter Author Name:";
	gets(atnm);
	cout<<"Enter Price:";
	cin>>price;
	status=0;
	rtrn=0;
    }
    void vwbk()
    {
	cout<<"\nBook ID:"<<bkid<<endl;
	cout<<"Book Name:"<<bnm<<endl;
	cout<<"Author Name:"<<atnm<<endl;
	cout<<"Price:"<<price<<endl;
	if(status==0)
	{
	    cout<<"Status:Not Issued";
	}
	else
	{
	    cout<<"Status:Issued to Member ID "<<status;
	    if(rtrn==0)
	    cout<<"\nReturn:No";
	}
	if(rtrn!=0)
	{
	 cout<<"\nReturn:Yes. By Member ID "<<rtrn;
	}
    }

}bk;
class member
{
 public:
    int mid;
    char mnm[100];
    char mob[20];
    int age;
    void input()
    {
	cout<<"\nEnter Member ID:";
	cin>>mid;
	cout<<"Enter Member Name:";
	gets(mnm);
	cout<<"Enter Mobile No.:";
	gets(mob);
	cout<<"Enter Age:";
	cin>>age;
    }
    void output()
    {
	cout<<"\nMember ID:"<<mid<<endl;
	cout<<"Member Name:"<<mnm<<endl;
	cout<<"Mobile No.:"<<mob<<endl;
	cout<<"Age:"<<age<<endl;
    }
}mr;
void addbook()
{
 fstream f1("lib.txt",ios::in|ios::out|ios::app);
 bk.acptbk();
 f1.write((char *)&bk,sizeof(bk));
 cout<<"\n. . . DATA ADDED. . .";
 f1.close();
}
void readbook()
{
 fstream f2("lib.txt",ios::in|ios::out|ios::app);
 f2.seekg(0);
 while(f2.read((char *)&bk,sizeof(bk)))
 {
  bk.vwbk();
  cout<<"\n";
 }
 f2.clear();
 f2.close();
 cout<<"\n. . . DATA DISPLAYED. .. .";
}
void searchbook()
{   int bid,k=0;
    fstream f3("lib.txt",ios::in|ios::out|ios::ate);
    cout<<"\nEnter book ID:";
    cin>>bid;
    f3.seekg(0,ios::beg);
    while(f3.read((char*)&bk,sizeof(bk)))
    {
	if(bk.bkid==bid)
	{
	 k=1;break;
	}
    }
    f3.clear();
    if(k==0)
     cout<<"\n. . .DATA NOT FOUND. . .";
    else
     {
      cout<<"\n.. . DATA FOUND. . .";
      bk.vwbk();
     }
    f3.close();
}
void editbook()
{   int m=0;
    fstream rd;
    rd.open("lib.txt",ios::in|ios::out|ios::ate);
    rd.seekg(0,ios::beg);
    int bookid;
    cout<<"Enter Book ID to edit:";
    cin>>bookid;
    while(rd.read((char*)&bk,sizeof(bk)))
    {
	if(bk.bkid==bookid)
	{
	  m=1;break;
	}
    }
    if(m==0)
     cout<<"\n. . . BOOK NOT FOUND. . .";
    else
    {
     char n[100],a[100];
     int pr,pos;
     pos=rd.tellp();
     rd.seekp(pos-sizeof(bk));
     cout<<"\nEnter New Book Name:";
     gets(n);
     cout<<"Enter New Author Name:";
     gets(a);
     cout<<"Enter New Price:";
     cin>>pr;
     strcpy(bk.bnm,n);
     strcpy(bk.atnm,a);
     bk.price=pr;
     cout<<"\nMODIFIED DATA\n";
     bk.vwbk();
    }
    rd.write((char*)&bk,sizeof(bk));
    rd.close();
}

void removebook()
{
    fstream rd,wr;
    rd.open("lib.txt",ios::in);
    wr.open("tmp.txt",ios::out);
    rd.seekg(0,ios::beg);
    int bookid;
    cout<<"\nEnter the Book ID to delete: ";
    cin>>bookid;
    while(rd.read((char*)&bk,sizeof(bk)))
     {
	if(bk.bkid!=bookid)
	    wr.write((char*)&bk,sizeof(bk));
    }
    rd.close();
    remove("lib.txt");
    wr.close();
    rename("tmp.txt","lib.txt");
    cout<<"\n. . .OPERATION DONE SUCCESSFULLY. . .";
}
void addmember()
{
    fstream wr;
    wr.open("ctr.txt",ios::in|ios::out|ios::app);
    mr.input();
    wr.write((char*)&mr,sizeof(mr));
    wr.close();
    cout<<"\n. . .MEMBER ADDED SUCCESSFULLY. . ."<<endl;
}
void viewmember()
{
 fstream f2("ctr.txt",ios::in);
 while(f2.read((char *)&mr,sizeof(mr)))
 {
  mr.output();
  cout<<"\n";
 }
 f2.close();
 cout<<"\n. . . MEMBER DISPLAYED. .. .";
}
void searchmember()
{
    fstream rd;
    rd.open("ctr.txt",ios::in);
    rd.seekg(0,ios::beg);
    int id,k=0;
    cout<<"Enter Member ID:";
    cin>>id;
    while(rd.read((char *)&mr,sizeof(mr)))
    {
    if(mr.mid==id)
	{
	 k=1;break;
	}
    }
    if(k==0)
     cout<<"\n. . . MEMBER NOT FOUND. . .";
    else
    {   cout<<"\n. . . MEMBER FOUND. . . ";
	mr.output();
     }
    rd.close();
}
void editmember()
{
    int m=0;
    fstream rd;
    rd.open("ctr.txt",ios::in|ios::out|ios::ate);
    rd.seekg(0,ios::beg);
    int id;
    cout<<"\nEnter Member ID to edit:";
    cin>>id;
    while(rd.read((char*)&bk,sizeof(bk)))
    {
	if(mr.mid==id)
	{
	  m=1;break;
	}
    }
    if(m==0)
     cout<<"\n. . .MEMBER NOT FOUND. . .";
    else
    {
     char n[100],a[20];
     int ag,pos;
     pos=rd.tellp();
     rd.seekp(pos-sizeof(bk));
     cout<<"\nEnter New Member Name:";
     gets(n);
     cout<<"Enter New Mobile No.:";
     gets(a);
     cout<<"Enter New Age:";
     cin>>ag;
     strcpy(mr.mnm,n);
     strcpy(mr.mob,a);
     mr.age=ag;
    }
    rd.write((char*)&bk,sizeof(bk));
    rd.close();
}
void deletemember()
{
    fstream rd,wr;
    rd.open("ctr.txt",ios::in);
    wr.open("temp.txt",ios::out);
    rd.seekg(0,ios::beg);
    int memberid;
    cout<<"enter member id:";
    cin>>memberid;
    while(rd.read((char*)&mr,sizeof(mr)))
	{
	if(mr.mid!=memberid)
	 wr.write((char*)&mr,sizeof(mr));
    }
    rd.close();
    remove("ctr.txt");
    wr.close();
    rename("temp.txt","ctr.txt");
    cout<<"\n. . . MEMBER DELETED. . . \n";
}
void issuebook()
{
    int bookid,k=0,f=0,pos;
    cout<<"\n\t\t. .BOOK ISSUE. .";
    cout<<"\nEnter Book ID:";
    cin>>bookid;
    fstream rd;
    rd.open("lib.txt",ios::in|ios::out|ios::ate);
    rd.seekg(0,ios::beg);
    while(rd.read((char*)&bk,sizeof(bk)))
    {
    if(bk.bkid==bookid&&bk.status==0)
    {
       k=1;break;
    }
    }
    if(k==0)
    {
     cout<<"\n. . . INVALID BOOK ID OR BOOK IS ALREADY ISSUED. . . ";
     goto end;
    }
    else
     bk.vwbk();
if(bk.status==0)
{
    cout<<"\n\n. . .NOW LET'S ISSUE BOOK. . .\n";
    int id,x=0;
    cout<<"\nEnter Member ID:";
    cin>>id;
    fstream wr,r;
    wr.open("isu.txt",ios::out);
    rd.seekg(0,ios::beg);
    r.open("ctr.txt",ios::in);
    r.seekg(0,ios::beg);
    while(r.read((char *)&mr,sizeof(mr)))
    {
    if(mr.mid==id)
	{
	 x=1;break;
	}
    }
   if(x==0)
     cout<<"\n. . . INVALID MEMBER. . .";
   else
   {
    while(rd.read((char*)&bk,sizeof(bk)))
    {
	if(bk.bkid==bookid)
	{
	    f=1;
	    cout<<"\n. . THE BOOK IS ISSUED TO. .";
	    mr.output();
	    break;
	}
    }
    if(f==1)
    {
      pos=rd.tellp();
     rd.seekp(pos-sizeof(bk));
     bk.status=id;
     bk.rtrn=0;
     rd.write((char *)&bk,sizeof(bk));
    }
    rd.close();
    r.close();
    wr.close();

    cout<<endl<<". . .BOOK ISSSUED SUCCESSFULLY. . .";
   }
}
else
{
    cout<<endl<<". . . BOOK ALREADY ISSUED. . .";

}
end:
cout<<". . . .";
}
void returnbook()
{
    int bookid,f;
    cout<<"\nEnter Book ID:";
    cin>>bookid;
    fstream rd;
    int pos;
    rd.open("lib.txt",ios::in|ios::out|ios::ate);
    rd.seekg(0,ios::beg);
    int flag=0;
    while(rd.read((char *)&bk,sizeof(bk)))
    {
	if(bk.bkid==bookid)
	{
	  flag = 1;
	  if(bk.status!=0)
	  {
	      flag=2;f=1;
	      break;
	  }
	 }
    }
    if(f==1)
    {
	pos=rd.tellp();
	rd.seekp(pos-sizeof(bk));
	bk.rtrn=bk.status;
	bk.status=0;
	rd.write((char *)&bk,sizeof(bk));
     }
    if(flag==0)
    {
	cout<<"\n. . .INVALID BOOK ID"<<endl;
    }
    else if(flag==1)
    {
      cout<<"\n. . .BOOK IS NOT ISSUED. . "<<endl;
    }
    else if(flag==2)
    {
	cout<<"\n. . .BOOK RETURNED SUCCESSFULLY. . .";

    }
    rd.close();
}
void issuedbooks()
{
 fstream f1;
 f1.open("lib.txt",ios::in);
 f1.seekg(0);
 cout<<"\n\t\t ALL ISSUED BOOKS\n";
 while(f1.read((char *)&bk,sizeof(bk)))
 {
  if(bk.status!=0 && bk.rtrn==0)
  {
    bk.vwbk();
    cout<<"\n";
   }
  }
 f1.close();
}
void rtrnbooks()
{
 fstream f1,f2;
 f1.open("lib.txt",ios::in);
 f1.seekg(0);
 cout<<"\n\t\tALL RETURNED BOOKS\n";
 while(f1.read((char *)&bk,sizeof(bk)))
 {
  if(bk.status==0 && bk.rtrn!=0)
  {
    bk.vwbk();
    cout<<"\n";
   }
  }
  f1.close();
}
void main()
{
 clrscr();
 int choice;
	do
	{
	    clrscr();
	    cout<<"\t\tCENTRAL LIBRARY DATABASE MANAGEMENT SYSTEM\n\n";
	    cout<<"MANAGE BOOKS";
	    cout<<setw(20)<<"MANAGE MEMBERS";
	    cout<<setw(20)<<"MANAGE WORK";
	    cout<<"\n1.Add book";
	    cout<<setw(20)<<"6.Add Member";
	    cout<<setw(24)<<"11.Issue Book"<<endl;
	    cout<<"2.View Books";
	    cout<<setw(20)<<"7.View Members";
	    cout<<setw(24)<<"12.Return Books"<<endl;
	    cout<<"3.Search book";
	    cout<<setw(21)<<"8.Search Members";
	    cout<<setw(27)<<"13.View Issued Books"<<endl;
	    cout<<"4.Edit book";
	    cout<<setw(21)<<"9.Edit Members";
	    cout<<setw(29)<<"14.View Return Books"<<endl;
	    cout<<"5.Remove book";
	    cout<<setw(22)<<"10.Remove Members";
	    cout<<setw(13)<<"15.Exit";

	    cout<<"\n\n\t\tEnter Your Choice:";
	    cin>>choice;
	    switch(choice)
	{
	case 1:
	    {
		addbook();
		break;
	    }
	 case 2:
	    {
		readbook();
		break;
	    }
	 case 3:
	    {
		searchbook();
	   break;
	    }
	 case 4:
	    {
		editbook();
		break;
	    }
	 case 5:
	    {
		removebook();
		break;
	    }
	 case 6:
	    {
		addmember();
		break;
	    }
	 case 7:
	    {
		viewmember();
		break;
	    }
	 case 8:
	    {
		searchmember();
		break;
	    }
	 case 9:
	    {
		editmember();
		break;
	    }
	 case 10:
	    {
		deletemember();
		break;
	    }
	 case 11:
	    {
		issuebook();
		break;
	    }
	 case 12:
	    {

		returnbook();
		break;
	    }
	case 13:
	    {
		issuedbooks();
		break;
	    }
	    case 14:
	    {
		 rtrnbooks();
		 break;
	    }
	    case 15:
	    {
		exit(0);
		break;
	    }
	 default:
	 cout<<"\n. . . WRONG CHOICE. . .";
	}
      getch();
    }while(choice!=15);
}
