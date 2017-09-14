#include "common.h"
#include "HttpProtocol.h"

char *CHttpProtocol::pass=PASSWORD;
CHttpProtocol::CHttpProtocol(void)
{
	bio_err=0;
	m_strRootDir="/home/WebServer";
	ErrorMsg="";
    //���������Ļ���
  ErrorMsg=initialize_ctx();
	if(ErrorMsg=="")
	{
		ErrorMsg=load_dh_params(ctx, ROOTKEYPEM);
	}
	else
	printf("%s \n",ErrorMsg);
}

CHttpProtocol::~CHttpProtocol(void)
{
	// �ͷ�SSL�����Ļ���
	SSL_CTX_free(ctx);
}

char * CHttpProtocol::initialize_ctx()
{
    SSL_METHOD *meth;
    
    if(!bio_err)
	{
		//��ʼ��OpenSSL��,����OpenSSL�����õ����㷨
		SSL_library_init();
		// ���ش����ַ���
		SSL_load_error_strings();	
		// An error write context 
		bio_err = BIO_new_fp(stderr, BIO_NOCLOSE);
    }
	else
	{
		return "initialize_ctx() error!";
	}
    
    // Create our context
    meth = SSLv23_method();
    ctx = SSL_CTX_new(meth);

    // ָ����ʹ�õ�֤���ļ�
    if(!(SSL_CTX_use_certificate_chain_file(ctx, SERVERPEM)))
	{
		char * Str = "SSL_CTX_use_certificate_chain_file error!";
		return Str;
	}

	// ��������ص�����
    SSL_CTX_set_default_passwd_cb(ctx, password_cb);

	// ����˽Կ�ļ�
    if(!(SSL_CTX_use_PrivateKey_file(ctx, SERVERKEYPEM, SSL_FILETYPE_PEM)))
	{
		char * Str = "SSL_CTX_use_PrivateKey_file error!";
		return Str;
	}

    // ���������ε�CA֤��
    if(!(SSL_CTX_load_verify_locations(ctx, ROOTCERTPEM, 0)))
	{
		char * Str = "SSL_CTX_load_verify_locations error!";
		return Str;
	}
	return "";
}

char * CHttpProtocol::load_dh_params(SSL_CTX *ctx, char *file)
{
    DH *ret = 0;
    BIO *bio;

    if ((bio = BIO_new_file(file,"r")) == NULL)
	{
		char * Str = "BIO_new_file error!";
		return Str;
	}

    ret = PEM_read_bio_DHparams(bio, NULL, NULL, NULL);
    BIO_free(bio);
    if(SSL_CTX_set_tmp_dh(ctx, ret) < 0)
	{
		char * Str = "SSL_CTX_set_tmp_dh error!";
		return Str;
	}
	return "";
}

int CHttpProtocol::password_cb(char *buf, int num, int rwflag, void *userdata)
{ 
    if((unsigned int)num < strlen(pass)+1)
	{
		return(0);
	}

    strcpy(buf, pass);
    return(strlen(pass));
}

void CHttpProtocol::err_exit(char * str)
{
	printf("%s \n",str);
	exit(1);
}

void CHttpProtocol::Disconnect(PREQUEST pReq)
{
	// �ر��׽��֣��ͷ���ռ�е���Դ
	int	nRet;
	printf("Closing socket! \r\n");
	
	nRet = close(pReq->Socket);
	if (nRet == SOCKET_ERROR)
	{
		// �������
		printf("Closing socket error! \r\n");
	}

//	HTTPSTATS	stats;
//	stats.dwRecv = pReq->dwRecv;
//	stats.dwSend = pReq->dwSend;
//	SendMessage(m_hwndDlg, DATA_MSG, (UINT)&stats, NULL);
}

void CHttpProtocol::CreateTypeMap()
{
	// ��ʼ��map
    m_typeMap[".doc"]	= "application/msword";
	m_typeMap[".bin"]	= "application/octet-stream";
	m_typeMap[".dll"]	= "application/octet-stream";
	m_typeMap[".exe"]	= "application/octet-stream";
	m_typeMap[".pdf"]	= "application/pdf";
	m_typeMap[".ai"]	= "application/postscript";
	m_typeMap[".eps"]	= "application/postscript";
	m_typeMap[".ps"]	= "application/postscript";
	m_typeMap[".rtf"]	= "application/rtf";
	m_typeMap[".fdf"]	= "application/vnd.fdf";
	m_typeMap[".arj"]	= "application/x-arj";
	m_typeMap[".gz"]	= "application/x-gzip";
	m_typeMap[".class"]	= "application/x-java-class";
	m_typeMap[".js"]	= "application/x-javascript";
	m_typeMap[".lzh"]	= "application/x-lzh";
	m_typeMap[".lnk"]	= "application/x-ms-shortcut";
	m_typeMap[".tar"]	= "application/x-tar";
	m_typeMap[".hlp"]	= "application/x-winhelp";
	m_typeMap[".cert"]	= "application/x-x509-ca-cert";
	m_typeMap[".zip"]	= "application/zip";
	m_typeMap[".cab"]	= "application/x-compressed";
	m_typeMap[".arj"]	= "application/x-compressed";
	m_typeMap[".aif"]	= "audio/aiff";
	m_typeMap[".aifc"]	= "audio/aiff";
	m_typeMap[".aiff"]	= "audio/aiff";
	m_typeMap[".au"]	= "audio/basic";
	m_typeMap[".snd"]	= "audio/basic";
	m_typeMap[".mid"]	= "audio/midi";
	m_typeMap[".rmi"]	= "audio/midi";
	m_typeMap[".mp3"]	= "audio/mpeg";
	m_typeMap[".vox"]	= "audio/voxware";
	m_typeMap[".wav"]	= "audio/wav";
	m_typeMap[".ra"]	= "audio/x-pn-realaudio";
	m_typeMap[".ram"]	= "audio/x-pn-realaudio";
	m_typeMap[".bmp"]	= "image/bmp";
	m_typeMap[".gif"]	= "image/gif";
	m_typeMap[".jpeg"]	= "image/jpeg";
	m_typeMap[".jpg"]	= "image/jpeg";
	m_typeMap[".tif"]	= "image/tiff";
	m_typeMap[".tiff"]	= "image/tiff";
	m_typeMap[".xbm"]	= "image/xbm";
	m_typeMap[".wrl"]	= "model/vrml";
	m_typeMap[".htm"]	= "text/html";
	m_typeMap[".html"]	= "text/html";
	m_typeMap[".c"]		= "text/plain";
	m_typeMap[".cpp"]	= "text/plain";
	m_typeMap[".def"]	= "text/plain";
	m_typeMap[".h"]		= "text/plain";
	m_typeMap[".txt"]	= "text/plain";
	m_typeMap[".rtx"]	= "text/richtext";
	m_typeMap[".rtf"]	= "text/richtext";
	m_typeMap[".java"]	= "text/x-java-source";
	m_typeMap[".css"]	= "text/css";
	m_typeMap[".mpeg"]	= "video/mpeg";
	m_typeMap[".mpg"]	= "video/mpeg";
	m_typeMap[".mpe"]	= "video/mpeg";
	m_typeMap[".avi"]	= "video/msvideo";
	m_typeMap[".mov"]	= "video/quicktime";
	m_typeMap[".qt"]	= "video/quicktime";
	m_typeMap[".shtml"]	= "wwwserver/html-ssi";
	m_typeMap[".asa"]	= "wwwserver/isapi";
	m_typeMap[".asp"]	= "wwwserver/isapi";
	m_typeMap[".cfm"]	= "wwwserver/isapi";
	m_typeMap[".dbm"]	= "wwwserver/isapi";
	m_typeMap[".isa"]	= "wwwserver/isapi";
	m_typeMap[".plx"]	= "wwwserver/isapi";
	m_typeMap[".url"]	= "wwwserver/isapi";
	m_typeMap[".cgi"]	= "wwwserver/isapi";
	m_typeMap[".php"]	= "wwwserver/isapi";
	m_typeMap[".wcgi"]	= "wwwserver/isapi";

}

int CHttpProtocol::TcpListen()
{
	  int sock;
    struct sockaddr_in sin;
    
    if((sock=socket(PF_INET,SOCK_STREAM,0))<0)
      err_exit("Couldn't make socket");
    
    memset(&sin,0,sizeof(sin));
    sin.sin_addr.s_addr=INADDR_ANY;
    sin.sin_family=PF_INET;
    sin.sin_port=htons(8000);
    
    if(bind(sock,(struct sockaddr *)&sin, sizeof(struct sockaddr))<0)
      err_exit("Couldn't bind");
    listen(sock,5); 
	//printf("TcpListen Ok\n");

    return sock;
}


bool CHttpProtocol::SSLRecvRequest(SSL *ssl,BIO *io, LPBYTE pBuf, DWORD dwBufSize)
{
	//printf("SSLRecvRequest \n");
	char buf[BUFSIZZ];
    int r, length=0;

	memset(buf, 0, BUFSIZZ);	//��ʼ��������
	while(1)
	{
		r = BIO_gets(io, buf, BUFSIZZ-1);
		//printf("r = %d\r\n",r);
		switch(SSL_get_error(ssl, r))
		{
			case SSL_ERROR_NONE:
				memcpy(&pBuf[length], buf, r);
				length += r;
				//printf("Case 1... \r\n");
				break;
			default:
				//printf("Case 2... \r\n");
				break;
		}
		// ֱ����������HTTPͷ�������Ŀ���
		if(!strcmp(buf,"\r\n") || !strcmp(buf,"\n"))
		{
			printf("IF...\r\n");
			break;
		}
  }
	// ��ӽ�����
	pBuf[length] = '\0';
	return true;
}
bool CHttpProtocol::StartHttpSrv()
{
	CreateTypeMap();
	
	printf("*******************Server starts************************ \n");
	
	pid_t pid;
	m_listenSocket = TcpListen();

	pthread_t listen_tid;
	pthread_create(&listen_tid,NULL,&ListenThread,this);
}

void * CHttpProtocol::ListenThread(LPVOID param)
{
		printf("Starting ListenThread... \n");
		
		CHttpProtocol *pHttpProtocol = (CHttpProtocol *)param;

		SOCKET		socketClient;
		pthread_t	client_tid;
		struct sockaddr_in	SockAddr;
		PREQUEST	pReq;
		socklen_t	nLen;
		DWORD		dwRet;

	while(1)	// ѭ���ȴ�,���пͻ���������,����ܿͻ�������Ҫ��
	{	
		//printf("while!\n");
		nLen = sizeof(SockAddr);		
		// �׽��ֵȴ�����,���ض�Ӧ�ѽ��ܵĿͻ������ӵ��׽���
		socketClient = accept(pHttpProtocol->m_listenSocket, (LPSOCKADDR)&SockAddr, &nLen);
		//printf("%s ",inet_ntoa(SockAddr.sin_addr));
		if (socketClient == INVALID_SOCKET)
		{  
			printf("INVALID_SOCKET !\n");
			break;
		}		
		pReq = new REQUEST;
		//pReq->hExit  = pHttpProtocol->m_hExit;
		pReq->Socket = socketClient;
		pReq->hFile = -1;
		pReq->dwRecv = 0;
		pReq->dwSend = 0;
		pReq->pHttpProtocol = pHttpProtocol;
		pReq->ssl_ctx=pHttpProtocol->ctx;

	    // ����client���̣�����request
		//printf("New request");
		pthread_create(&client_tid,NULL,&ClientThread,pReq);
	} //while

		return NULL;
}
	
void * CHttpProtocol::ClientThread(LPVOID param)
{
	printf("Starting ClientThread... \n");
	int nRet;
	SSL *ssl;
	BYTE buf[4096];
	BIO *sbio,*io, *ssl_bio;
	PREQUEST pReq = (PREQUEST)param;
	CHttpProtocol *pHttpProtocol = (CHttpProtocol *)pReq->pHttpProtocol;
	//pHttpProtocol->CountUp();				// ����
	SOCKET s = pReq->Socket;
	
	sbio = BIO_new_socket(s, BIO_NOCLOSE);	// ����һ��socket���͵�BIO����
	ssl=SSL_new(pReq->ssl_ctx);				// ����һ��SSL����
  SSL_set_bio(ssl, sbio, sbio);			// ��SSL����󶨵�socket���͵�BIO��
	//���ӿͻ��ˣ���SSL_accept�����У�����ռ�úܴ��cpu
    nRet = SSL_accept(ssl);
	//nRet<=0ʱ��������
    if(nRet <= 0)
		{
			pHttpProtocol->err_exit("SSL_accept()error! \r\n");
			//return 0;
		}
		
    io = BIO_new(BIO_f_buffer());			//��װ�˻�����������BIO��д��ýӿڵ�����һ����׼����
											//����һ��BIO�ӿڵģ��Ӹýӿڶ���������һ��Ҳ�Ǵ���һ
											//��BIO�������ġ�
    ssl_bio = BIO_new(BIO_f_ssl());			//��װ��openssl ��SSLЭ���BIO���ͣ�Ҳ����ΪSSLЭ����
											//����һЩBIO����������
    BIO_set_ssl(ssl_bio, ssl, BIO_CLOSE);	// ��ssl(SSL����)��װ��ssl_bio(SSL_BIO����)��
    BIO_push(io, ssl_bio);					// ��ssl_bio��װ��һ�������BIO�����У����ַ�������
											// ����ʹ��BIO_*�����������������͵�IO����,�Ӷ�ʵ�ֶ�SSL���ӵĻ������д 
	
	// ����request data
	printf("****************\r\n");
	if (!pHttpProtocol->SSLRecvRequest(ssl,io,buf,sizeof(buf)))
	{
		// �������
		pHttpProtocol->err_exit("Receiving SSLRequest error!! \r\n");
	}
	else
	{
			printf("Request received!! \n");
			printf("%s \n",buf);		
			//return 0;								
	}
	nRet = pHttpProtocol->Analyze(pReq, buf);
	if (nRet)
	{	
		// �������
		pHttpProtocol->Disconnect(pReq);
		delete pReq;
		pHttpProtocol->err_exit("Analyzing request from client error!!\r\n");
	}

	// ���ɲ�����ͷ��
	if(!pHttpProtocol->SSLSendHeader(pReq,io))
	{
		pHttpProtocol->err_exit("Sending fileheader error!\r\n");
	}
	BIO_flush(io);

	// ��client��������
	if(pReq->nMethod == METHOD_GET)
	{
		printf("Sending..............................\n");
		if(!pHttpProtocol->SSLSendFile(pReq,io))
		{
			return 0;
		}
	}
	printf("File sent!!");
	//pHttpProtocol->Test(pReq);
	pHttpProtocol->Disconnect(pReq);
	delete pReq;
	SSL_free(ssl);
	return NULL;
}

int  CHttpProtocol::Analyze(PREQUEST pReq, LPBYTE pBuf)
{
	// �������յ�����Ϣ
	char szSeps[] = " \n";
	char *cpToken;
	// ��ֹ�Ƿ�����
	if (strstr((const char *)pBuf, "..") != NULL)
	{
		strcpy(pReq->StatuCodeReason, HTTP_STATUS_BADREQUEST);
		return 1;
	}

	// �ж�ruquest��mothed	
	cpToken = strtok((char *)pBuf, szSeps);	// �������ַ����ֽ�Ϊһ���Ǵ���	
	if (!strcmp(cpToken, "GET"))			// GET����
	{
		pReq->nMethod = METHOD_GET;
	}
	else if (!strcmp(cpToken, "HEAD"))	// HEAD����
	{
		pReq->nMethod = METHOD_HEAD;  
	}
	else  
	{
        strcpy(pReq->StatuCodeReason, HTTP_STATUS_NOTIMPLEMENTED);
		return 1;
	}

	// ��ȡRequest-URI
	cpToken = strtok(NULL, szSeps);
	if (cpToken == NULL)   
	{
		strcpy(pReq->StatuCodeReason, HTTP_STATUS_BADREQUEST);
		return 1;
	}

	strcpy(pReq->szFileName, m_strRootDir);
	if (strlen(cpToken) > 1)
	{
		strcat(pReq->szFileName, cpToken);	// �Ѹ��ļ�����ӵ���β���γ�·��
	}
	else
	{
		strcat(pReq->szFileName, "/index.html");
	}
	printf("%s\r\n",pReq->szFileName);
	
	return 0;
}

int CHttpProtocol::FileExist(PREQUEST pReq)
{
	pReq->hFile = open(pReq->szFileName,O_RDONLY);
	// ����ļ������ڣ��򷵻س�����Ϣ
	if (pReq->hFile == -1)
	{
		strcpy(pReq->StatuCodeReason, HTTP_STATUS_NOTFOUND);
		printf("open %s error\n",pReq->szFileName);
		return 0;
	}
	else 
	{
		//printf("hFile\n");
		return 1;
	}
}
void CHttpProtocol::Test(PREQUEST pReq)
{
		struct stat buf;
		long fl;
		if(stat(pReq->szFileName, &buf)<0)
		{
		   err_exit("Getting filesize error!!\r\n");
		}
		fl = buf.st_size;
		printf("Filesize = %d \r\n",fl);
}

void CHttpProtocol::GetCurrentTime(LPSTR lpszString)
{
	// ��������ʱ�������ת��
	char *week[] = {"Sun,", "Mon,","Tue,","Wed,","Thu,","Fri,","Sat,",};
	// ��������ʱ����·�ת��
	char *month[] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec",};
	// �����ʱ��
	struct tm *st;
	long ct;
	ct = time(&ct);
	st = (struct tm *)localtime(&ct);
	// ʱ���ʽ��
    sprintf(lpszString, "%s %02d %s %d %02d:%02d:%02d GMT",week[st->tm_wday], st->tm_mday, month[st->tm_mon],
     1900+st->tm_year, st->tm_hour, st->tm_min, st->tm_sec);
}


bool CHttpProtocol::GetContentType(PREQUEST pReq, LPSTR type)
{
	// ȡ���ļ�������
    char * cpToken;
    cpToken = strstr(pReq->szFileName, ".");
    strcpy(pReq->postfix, cpToken);
	// �����������ļ����Ͷ�Ӧ��content-type
	map<char *, char *>::iterator it = m_typeMap.find(pReq->postfix);
	if(it != m_typeMap.end())
	{
		sprintf(type,"%s",(*it).second);
	}
	return 1;
}


bool CHttpProtocol::SSLSendHeader(PREQUEST pReq, BIO *io)
{
	char Header[2048] = " ";
	int n = FileExist(pReq);
	if(!n)		// �ļ������ڣ��򷵻�
	{
    err_exit("The file requested doesn't exist!");
	}

	char curTime[50];
	GetCurrentTime(curTime);
	// ȡ���ļ�����
	struct stat buf;
	long length;
	if(stat(pReq->szFileName, &buf)<0)
	{
	   err_exit("Getting filesize error!!\r\n");
	}
	length = buf.st_size;
	
	// ȡ���ļ�������
	char ContentType[50] = " ";
 	GetContentType(pReq, (char*)ContentType);

	sprintf((char*)Header, "HTTP/1.1 %s\r\nDate: %s\r\nServer: %s\r\nContent-Type: %s\r\nContent-Length: %d\r\n\r\n",
			                    HTTP_STATUS_OK, 
								curTime,				// Date
								"Villa Server 192.168.1.49",      // Server"My Https Server"
								ContentType,				// Content-Type
								length);					// Content-length
								
	//if(BIO_puts(io, Header) <= 0)//����
	if(BIO_write(io, Header,strlen(Header)) <= 0)//����
	{
		return false;
	}
	BIO_flush(io);
	printf("SSLSendHeader successfully!\n");
	return true;
}


bool CHttpProtocol::SSLSendFile(PREQUEST pReq, BIO *io)
{
	//printf("%s\n",pReq->szFileName);
	int n = FileExist(pReq);
	// ���������ļ������ڣ��򷵻�
	if(!n)			
	{
		err_exit("The file requested doesn't exist!");
	}

	static char buf[2048];
    DWORD  dwRead;
    BOOL   fRet;
	int flag = 1,nReq;
    // ��д����ֱ�����
    while(1)
	{	
		// ��file�ж��뵽buffer��        
		fRet = read(pReq->hFile, buf, sizeof(buf));
		//printf("%d,%d\n",fRet,pReq->hFile);
		if (fRet<0)
		{
			//printf("!fRet\n");
	    	static char szMsg[512];
		    sprintf(szMsg, "%s", HTTP_STATUS_SERVERERROR);
        	// ��ͻ��˷��ͳ�����Ϣ
			//if((nReq = BIO_puts(io, szMsg)) <= 0)//����
			if((nReq = BIO_write(io, szMsg,strlen(szMsg))) <= 0)//����
			{
				err_exit("BIO_write() error!\n");
			}
			BIO_flush(io);
	    	break;
		}
		
		// ���
		if (fRet == 0)
		{	
			printf("complete \n");
			break;
		}
		// ��buffer���ݴ��͸�client
		//if(BIO_puts(io, buf) <= 0)//����
		if(BIO_write(io, buf, fRet) <= 0)
		{
			if(! BIO_should_retry(io))
			{
				printf("BIO_write() error!\r\n");
				break;
			}
		}
		BIO_flush(io);
		//ͳ�Ʒ�������
		pReq->dwSend+=fRet;
	}
    // �ر��ļ�
	if (close(pReq->hFile)==0)
	{
		pReq->hFile = -1;
		return true;
	}
	else//����
	{
		err_exit("Closing file error!");
	}
}
