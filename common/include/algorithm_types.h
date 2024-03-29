﻿#ifndef ALGORITHM_TYPES_H
#define ALGORITHM_TYPES_H

#define HASHFILE_MAX_PLAIN_LENGTH 192
#define HASHFILE_MAX_SALT_LENGTH 32
#define HASHFILE_MAX_LINE_LENGTH 256	

enum crack_charset
{
	charset_num,		//0123456789
	charset_lalpha,		//abcdefghijklmnopqrstuvwxyz
	charset_ualpha,		//ABCDEFGHIJKLMNOPQRSTUVWXYZ
	charset_alpha,		//l_alpha+ualpha
	charset_lalphanum,	//lalpha+num
	charset_ualphanum,	//ualpha+num
	charset_alphanum,	//alpha+num
	charset_ascii,		//alpha+num+~!@#$%^&*()_+{}|":?><-=[]\';/.,
	charset_custom,		//自己定义
};

//字典名请按照dict-%d.txt格式命名
enum crack_dict
{
	dict_english,			//字典1
	dict_birthday,			//字典2	
};

static const char* crack_charsets[] = 
{
	"0123456789",
	"abcdefghijklmnopqrstuvwxyz",
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ",
	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ",
	"abcdefghijklmnopqrstuvwxyz0123456789",
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789",
	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789",
	"abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ !@#$%^&*()-_=+[]{}|\\\'\";:`~<>,./?",
	""
};

enum crack_type
{
	bruteforce,
	dict,
	rule,
	mask,
	rainbow,
	max_value
};

enum crack_algorithm
{
	algo_md4=0x01,        //MD4 plugin
	algo_md5,             //MD5 plugin
	algo_md5md5,          //md5(md5(pass)) plugin
	algo_md5unix,         //MD5(Unix) plugin (shadow files)
	algo_mediawiki,       //md5(salt.'-'.md5(password)) plugin (Wikimedia)
	algo_oscommerce,      //md5(salt,password) plugin (osCommerce)
	algo_ipb2,            //md5(md5(salt).md5(pass)) plugin (IPB > 2.x)
	algo_joomla,          //md5(password,salt) plugin (joomla)
	algo_vbulletin,       //md5(md5(pass).salt) plugin
	algo_desunix,         //DES(Unix) plugin (.htpasswd)
	algo_sha1,            //SHA1 plugin
	algo_sha1sha1,        //sha1(sha1(pass)) plugin
	algo_sha256,          //SHA-256 plugin
	algo_sha256unix,      //SHA256(Unix) plugin (shadow files)
	algo_sha512,          //SHA-512 plugin
	algo_sha512unix,      //SHA512(Unix) plugin (shadow files)
	algo_msoffice_old,    //MS Office XP/2003 plugin
	algo_msoffice,        //MS Office 2007/2010/2013 plugin
	algo_django256,       //Django SHA-256 plugin
	algo_zip,             //ZIP passwords plugin
	algo_rar,             //RAR3 passwords plugin
	algo_apr1,            //Apache apr1 plugin
	algo_bfunix,          //bfunix plugin (shadow files)
	algo_dmg,             //FileVault (v1)  passwords plugin
	algo_drupal7,         //Drupal >=7 hashes plugin
	algo_lm,              //LM plugin
	algo_luks,            //LUKS encrypted block device plugin
	algo_mscash,          //Domain cached credentials plugin
	algo_mscash2,         //Domain cached credentials v2 plugin
	algo_mssql_2000,      //Microsoft SQL Server 2000 plugin
	algo_mssql_2005,      //Microsoft SQL Server 2005 plugin
	algo_mssql_2012,      //Microsoft SQL Server 2012 plugin
	algo_mysql5,          //MySQL > 4.1 plugin
	algo_nsldap,          //LDAP SHA plugin
	algo_nsldaps,         //LDAP SSHA (salted SHA) plugin
	algo_ntlm,            //NTLM plugin
	algo_o5logon,         //Oracle TNS O5logon
	algo_oracle_old,      //Oracle 7 up to 10r2 plugin
	algo_oracle11g,       //Oracle 11g plugin
	algo_osx_old,         //MacOSX <= 10.6 system passwords plugin
	algo_osxlion,         //MacOSX Lion system passwords plugin
	algo_phpbb3,          //phpBB3 hashes plugin
	algo_pixmd5,          //Cisco PIX password hashes plugin
	algo_privkey,         //SSH/SSL private key passphrase plugin
	algo_ripemd160,       //RIPEMD-160 plugin
	algo_sapg,            //SAP CODVN G passwords plugin
	algo_sl3,             //Nokia SL3 plugin
	algo_smf,             //SMF plugin
	algo_wordpress,       //Wordpress hashes plugin
	algo_wpa,             //WPA-PSK plugin
	algo_pdf,             //Adoble PDF document plugin
	algo_max			  //MAX
};

//hash
struct crack_hash
{
	char hash[HASHFILE_MAX_PLAIN_LENGTH+4];
	char salt[HASHFILE_MAX_SALT_LENGTH];
	char salt2[HASHFILE_MAX_SALT_LENGTH];
};

struct crack_task;

//workitem
struct crack_block
{
	unsigned char algo;		//解密算法
	unsigned char charset;	//解密字符集
	unsigned char type;		//解密类型
	unsigned char special;//是否是文件解密（pdf+office+rar+zip）
	int hash_idx;				//指向所属的hash
	char guid[40];			//服务端的workitem的GUID
	char john[sizeof(struct crack_hash)];		//原始Hash格式：hash值+盐
	union{
		struct{
			unsigned short start;	//开始长度
			unsigned short end;		//结束长度
		};
		
		struct{
			unsigned char dict_idx;//字典索引
		};
		
		struct{
			unsigned short maskLength:8;	//长度
			unsigned short flag:8;			//0表示task中给定的算法类型就是掩码；1表示task中给定的算法类型是暴力破解中切分出来的
			union{
				char masks[18];				//掩码值(字符串138??????表示前3位为138，后6位为指定的charset值)
				struct{
					char masks1[9];				//起始掩码值 (aa?????-az?????)
					char masks2[9];				//终结掩码值 (aa?????-az?????)
				};
			};
		};
	};
		
#if defined(WIN64) || defined(X64)	
	struct crack_task* task;	//指向所属的task
#else
	struct crack_task* task;
	int padding;
#endif
};

//解密任务
struct crack_task
{
	unsigned char algo;		//解密算法
	unsigned char charset;	//解密字符集
	unsigned char type;		//解密类型
	unsigned char special:7;//是否是文件解密（pdf+office+rar+zip）
	unsigned char single:1;	//单个hash值（不通过文件）
	union{
		struct{
			unsigned char startLength;	//起始长度
			unsigned char endLength;	//终结长度
		};//暴力破解
		struct{
			unsigned char dict_idx;		//字典索引
		};//字典破解
		struct{
			unsigned short maskLength;	//长度
			char masks[18];				//掩码值(字符串138??????表示前3位为138，后6位为指定的charset值)
		};//掩码破解
	};
	unsigned char filename[256];	//用户传过来的文件名
	char guid[40];			//用户端的任务的GUID
	int count;				//需要解密的Hash个数（如果是文件=1）
	char padding[4];		//对齐需要	
#if defined(WIN64) || defined(X64)
	struct crack_hash* hashes;			//这里需要动态申请
#else
	struct crack_hash* hashes;			//这里需要动态申请
	char padding2[4];					//对齐需要	
#endif
	
};

//这里描述一下crack_task/crack_hash/crack_block三者的关系
//用户上传一个解密任务（解密文件、算法、字符集、字符长度），
//服务端解析文件得到若干个crack_hash（可以保存在crack_task里面，需要动态申请），
//然后切割算法将其分割成若干个crack_block

struct crack_status
{
	char guid[40];				//workitem/crack_block的GUID
	unsigned int progress;		//进度	
	float speed;				//速度
	unsigned int remainTime;	//剩余时间
};

struct crack_result
{
	char guid[40];			//workitem/crack_block的GUID
	unsigned int status;	//workitem的结果状态
	char password[32];		//如果解密成功，存放密码
};

#endif