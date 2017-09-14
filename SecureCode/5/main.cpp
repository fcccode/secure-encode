//==================================
//ͷ�ļ�
//==================================
#include "md5.h"
#include <iostream>

using namespace std;

//==================================
//���ܺ���
//==================================

//==================================
//Main����
//==================================
int main(int argc,char* argv[])
{
	  char* pFilePath;                     //��Ҫ����md5������ļ�·��
	  char* pMd5FilePath;                  //���md5ժҪ��.md5�ļ�·��
	  char  Md5Digest[33];                 //md5ժҪ�����ڴ���ֶ������md5ժҪ��Ϣ
	  char  Md5Record[50];                 //.md5�ļ��е�һ�м�¼
	  string strTmp;
	  
	  //======================================================================
	  //�ַ�������
		char* pHelpMsg =    {"-h"};          // ������Ϣ
		char* pTestMsg =    {"-t"};          // md5���Գ����Ӧ����Ϣ
		char* pCompute =    {"-c"};          // ����ָ���ļ���md5ժҪ
		char* pMValidate =  {"-mv"};         // �ֶ����ļ�����md5��֤
		char* pfValidate =  {"-fv"};		     // ͨ���Ƚ϶��ļ���md5ժҪ������֤
		char* pSpace = {" "};                // ����ո�
		
		//=======================================================================
		//�������
		if(argc<2 || argc>4)
		{
			cout<<"Parameter Error !"<<endl;
			return -1;
		}
		
		//=======================================================================
		//��ʾ������Ϣ
		if((argc == 2)&&(!strcmp(pHelpMsg,argv[1])))
		{
			cout<<"MD5 usage:  [-h]  --help information"<<endl;
			cout<<"            [-t]  --test MD5 application"<<endl;
			cout<<"            [-c]  [file path of the file computed]"<<endl;
			cout<<"                  --compute MD5 of the given file"<<endl;
			cout<<"            [-mv] [file path of the file validated]"<<endl;
			cout<<"                  --validate the integrality of a given file by manual input MD5 value"<<endl;
			cout<<"            [-fv] [file path of the file validated]  [file path of the .md5 file]"<<endl;
			cout<<"                  --validate the integrality of a given file by read MD5 value from .md5 file"<<endl;
		}
		
		//=======================================================================
		//��ʾmd5Ӧ�ó���Ĳ�����Ϣ
		if((argc == 2)&&(!strcmp(pTestMsg,argv[1])))
		{
			cout<<"MD5(\"\") = "<<MD5("").toString()<<endl;
			cout<<"MD5(\"a\") = "<<MD5("a").toString()<<endl;
			cout<<"MD5(\"abc\") = "<<MD5("abc").toString()<<endl;
			cout<<"MD5(\"message digest\") = "<<MD5("message digest").toString()<<endl;
			cout<<"MD5(\"abcdefghijklmnopqrstuvwxyz\") = "<<MD5("abcdefghijklmnopqrstuvwxyz").toString()<<endl;
			cout<<"MD5(\"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789\")"<<endl;
			cout<<"    = "<<MD5("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789").toString()<<endl;
			cout<<"MD5(\"12345678901234567890123456789012345678901234567890123456789012345678901234567890\")"<<endl;
			cout<<"    = "<<MD5("12345678901234567890123456789012345678901234567890123456789012345678901234567890").toString()<<endl;
		}
		
		//=======================================================================
		//����ָ���ļ���md5ժҪ������ʾ����
		if((argc == 3)&&(!strcmp(pCompute,argv[1])))
		{
			//���û���ļ�·�������������
			if(argv[2] == NULL)
			{
				cout<<"Parameter Error ! Please input file path !"<<endl;
				return -1;				
			}
			else
			{
				pFilePath = argv[2];
			}
			//��ָ�����ļ�
			ifstream File_1(pFilePath);
			//����md5����,�����м���
			MD5 md5_obj1(File_1);
			//���������
			cout<<"MD5(\""<<argv[2]<<"\") = "<<md5_obj1.toString()<<endl;
		}
		
		//=======================================================================
		//�ֶ������ļ������Լ��
		if((argc == 3)&&(!strcmp(pMValidate,argv[1])))
		{
			//���û���ļ�·�������������
			if(argv[2] == NULL)
			{
				cout<<"Parameter Error ! Please input file path !"<<endl;
				return -1;				
			}
			else
			{
				pFilePath = argv[2];
			}
      //�ֶ������˱����ļ���MD5ժҪ
			cout<<"Please input the MD5 value of file(\""<<pFilePath<<"\")..."<<endl;
     	cin>>Md5Digest;
     	//��ժҪ���ַ���ĩβ���Ͻ�����
     	Md5Digest[32] = '\0';
     	
			//��ָ�����ļ�
			ifstream File_2(pFilePath);
			//����md5����,�����м���
			//MD5 md5_obj2(File_2);
			MD5 md5_obj2;
			md5_obj2.reset();
			md5_obj2.update(File_2);
			
			//��ȡ�ļ����ݲ�����MD5ժҪ
			strTmp = md5_obj2.toString();
			const char* pMd5Digest = strTmp.c_str();
			
			//�������ժҪ
			cout<<"The MD5 digest of file(\""<<pFilePath<<"\") which you input is: "<<endl;
			cout<<Md5Digest<<endl;
			cout<<"The MD5 digest of file(\""<<pFilePath<<"\") which calculate by program is: "<<endl;
			cout<<strTmp<<endl;
			
		  //�Ƚ�ժҪ�Ľ���Ƿ���ͬ
			if (strcmp(pMd5Digest,Md5Digest))
			{
				cout<<"Match Error! The file is not integrated!"<<endl;
			}
			else
			{
				cout<<"Match Successfully! The file is integrated!"<<endl;
			}
		}
		//=======================================================================
		//ͨ��.md5�ļ������ļ������Լ��
		if((argc == 4)&&(!strcmp(pfValidate,argv[1])))
		{
			//���û���ļ�·�������������
			if((argv[2] == NULL)||(argv[3] == NULL))
			{
				cout<<"Parameter Error ! Please input file path !"<<endl;
				return -1;				
			}
			else
			{
				pFilePath = argv[2];
				pMd5FilePath = argv[3];
			}
			
			//��.md5�ļ�
			ifstream File_3(pMd5FilePath);
			//��ȡ.md5�ļ��еļ�¼
			File_3.getline(Md5Record,50);
			
	    //�Կո�Ϊ���,���.MD5�ļ��е�MD5ֵ���Ӧ�ļ���
	    char* pMd5Digest_f = strtok(Md5Record,pSpace);
	    char* pFileName_f = strtok(NULL,pSpace);
	   
		  //�򿪱����ļ�
		  ifstream File_4(pFilePath);
			//����md5����,�����м���
			//MD5 md5_obj3(File_4);
			MD5 md5_obj3;
			md5_obj3.reset();
			md5_obj3.update(File_4);
					  
			//��ȡ�ļ����ݲ�����MD5ժҪ
			strTmp = md5_obj3.toString();
			const char* pMd5Digest_c = strTmp.c_str();	   
			
			//�������ժҪ
			cout<<"The MD5 digest of file(\""<<pFileName_f<<"\") which is in file(\""<<pMd5FilePath<<"\") is: "<<endl;
			cout<<pMd5Digest_f<<endl;
			cout<<"The MD5 digest of file(\""<<pFilePath<<"\") which calculate by programme is: "<<endl;
			cout<<strTmp<<endl;
			
     //�Ƚ�ժҪ��������֤
	    if (strcmp(pMd5Digest_c,pMd5Digest_f)) 
			{
				cout<<"Match Error! The file is not integrated!"<<endl;
			}
			else
			{
				cout<<"Match Successfully! The file is integrated!"<<endl;
			}				
		}
    //��������
		return 0;
}
