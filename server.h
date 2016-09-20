/*
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 as
* published by the Free Software Foundation.
*
*
* Version: 1.0
*
* Authors:
*   wanglu <1048274411@qq.com>
*
*/
#ifndef _TINYMQ_SERVER_H_
#define _TINYMQ_SERVER_H_

#include <string>
#include <map>
#include <set>
#include <ext/hash_map>
namespace tinymq {

	class tinyServer
	{
	private:
		struct str_hash {
			size_t operator()(const std::string& str) const
			{
				return __gnu_cxx::__stl_hash_string(str.c_str());
			}
		};
		struct compare_str {
			bool operator()(const std::string& p1, const std::string& p2) const {
				return p1.compare(p2) == 0;
			}
		};
	public:
		static  tinyServer* instance();
		void deleteSession(const std::string& clientid);

		//����delete��Ӧ�ĻỰ���󣬽���_sessions map���Ƴ�
		void eraseSession(const std::string& clientid);
		void addSession(const std::string& clientid, tinySession * session);
		/*
			���ûỰ
			����true���ҵ��ɻỰ�ɹ�����
			����false��û�оɻỰ���½��Ự�ɹ�
		*/
		bool reuseSession(const std::string& clientid, tinySocket* sock);
		void addWaittingSock(clientEventProcessor *, time_t);
		void removeWaittingSock(clientEventProcessor *);
		bool addTopicSubscriber(const std::string&, tinySession*, char qos);
		__gnu_cxx::hash_map<const std::string, std::map<tinySession*, char>*, str_hash, compare_str>  _topicSubscriber;
		std::map<std::string, tinySession*> getSessions();
		std::map<clientEventProcessor*, time_t> getWaittingConnections();

	public:
		pthread_mutex_t  sessionMutex;
		pthread_mutex_t  wConnectionMutex;

	private:
		bool _addTopic(const std::string&, tinySession*, char qos);

	private:
		tinyServer() {
			sessionMutex = PTHREAD_MUTEX_INITIALIZER;
			wConnectionMutex = PTHREAD_MUTEX_INITIALIZER;
		}
		std::map<std::string, tinySession*> _sessions; //�Ựid����Ự����ָ��
		std::map<clientEventProcessor*, time_t> _waittingConnection;//����socket���Ӻ�ȴ�����mqtt connect���ĵ�map�������ʱ��Ͽ�����
	//	static tinyServer* _instance;
	};

}


#endif /*TINYMQ_SERVER_H_*/