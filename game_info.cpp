#include<iostream>
#include<winsock2.h>
using namespace std;

int main()
{
	char query[]="\xFF\xFF\xFF\xFF\x54\x53\x6F\x75\x72\x63\x65\x20\x45\x6E\x67\x69\x6E\x65\x20\x51\x75\x65\x72\x79\x00";
	char ip[16];
	char result[4096];
	int len;
	WSADATA data;
	if(WSAStartup(MAKEWORD(2,2),&data)==0)
	{
		cout<<"Enter the ip>>";
		cin>>ip;
		sockaddr_in servAdr;
		servAdr.sin_family=AF_INET;
		servAdr.sin_addr.S_un.S_addr=inet_addr(ip);
		servAdr.sin_port=htons(27015);
		SOCKET client= socket(AF_INET,SOCK_DGRAM,IPPROTO_IP);
		if(connect(client, (sockaddr*)&servAdr,sizeof(servAdr))==0)
		{
			cout<<"Connected!!"<<endl;
			len=sizeof(query);
			send(client,(char*)&query,len,0);
			recv(client,(char*)&result,4096,0);
			int i;
			cout<<"Result:"<<endl;
			cout<<"Server name: ";
			for(i=6;result[i]!='\x00';i++) cout<<result[i];
			cout<<endl;
			cout<<"Map: ";
			i++;
			for(;result[i]!='\x00';i++) cout<<result[i];
			cout<<endl;
			i++;
			cout<<"Folder: ";
			for(;result[i]!='\x00';i++) cout<<result[i];
			cout<<endl;
			i++;
			cout<<"Game: ";
			for(;result[i]!='\x00';i++) cout<<result[i];
			cout<<endl;
			i++;
			i++;
			i++;
			cout<<"Number of players: "<<(int)result[i]<<endl;
			i++;
			cout<<"Max number of players: "<<(int)result[i]<<endl;
			i++;
			cout<<"Number of Bots: "<<(int)result[i]<<endl;
			i++;
			cout<<"Server type: "<<result[i]<<endl;
			i++;
			cout<<"OS: "<<result[i]<<endl;
			i++;
			cout<<"Visibility: "<<(int)result[i]<<endl;
			i++;
			cout<<"VAC Secured: "<<(int)result[i]<<endl;
			cin.ignore();
			cin.get();
		}
		else
			cout<<"No game running";
	}
}
