#ifndef _TINYMQ_SERVER_H_
#define _TINYMQ_SERVER_H_

#include <string>
#include <map>
#include <set>
#include <ext/hash_map>
namespace tinymq {

	class tinyServer
	{
	public:
		static  tinyServer* instance();
		void deleteSession(const std::string& clientid);

		//����delete��Ӧ�ĻỰ����
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
		bool addTopicSubscriber(const std::string&, clientEventProcessor*);
		//__gnu_cxx::hash_map<int, std::set<clientEventProcessor*>>  test;
	private:
		bool _addTopic(const std::string&, clientEventProcessor*);
	private:
		tinyServer() {};
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
		__gnu_cxx::hash_map<const std::string, std::set<clientEventProcessor*>*, str_hash, compare_str>  _topicSubscriber;

		//std::map< std::string, std::set<clientEventProcessor*>>  _topicSubscriber;
		std::map<std::string, tinySession*> _sessions;
		std::map<clientEventProcessor*, time_t> _waittingConnection;
		static tinyServer* _instance;
	};

}


#endif /*TINYMQ_SERVER_H_*/