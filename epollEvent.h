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
#ifndef _TINYMQ_EPOLLEVENT_H_
#define _TINYMQ_EPOLLEVENT_H_


#define MAX_SOCKET_EVENTS 200
#include <vector>
namespace tinymq{

	class epollEvent
	{
	public:
		epollEvent();
		~epollEvent();
	   /*
        * ����tinySocket���¼���
        *
        * @param tinySocket ���ӵ�socket
        * @param enableRead: �����Ƿ�ɶ�
        * @param enableWrite: �����Ƿ��д
        * @return  �����Ƿ�ɹ�, true �C �ɹ�, false �C ʧ��
        */
		bool addEvent(tinySocket *socket, bool enableRead, bool enableWrite);

	    /*
	     * ����tinySocket���¼���
		 *
		 * @param socket ���ӵ�socket
		 * @param enableRead: �����Ƿ�ɶ�
		 * @param enableWrite: �����Ƿ��д
		 * @return  �����Ƿ�ɹ�, true �C �ɹ�, false �C ʧ��
		 */
		bool setEvent(tinySocket *socket, bool enableRead, bool enableWrite);

	   /*
	    * ɾ��tinySocket���¼���
		*
		* @param socket ��ɾ��socket
		* @return  �����Ƿ�ɹ�, true �C �ɹ�, false �C ʧ��
		*/
		bool removeEvent(tinySocket *socket);

		/*
		 * �õ���д�¼���
		 *
		 * @param timeout  ��ʱʱ��(��λ:ms)
		 * @param events  �¼�����
		 * @param cnt   events�������С
		 * @return �¼���, 0Ϊ��ʱ
		 */
		int getEvents(int timeout, std::vector<eventProcessor *>& events, int cnt);
		
	private:
		int _iepfd; // epoll fd
	};
	
}

#endif
