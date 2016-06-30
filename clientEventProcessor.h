#ifndef _CLIENTEVENTPROCESSER_H_
#define _CLIENTEVENTPROCESSER_H_
namespace tinymq{

	enum phase
	{
		START
		
	};
	class clientEventProcessor : public eventProcessor
	{
	public:
		clientEventProcessor(tinySocket *tSock);
		~clientEventProcessor();
		 bool handleReadEvent();
		 bool handleWriteEvent();
		 int getSocketHandle();
	private:
		bool headerProcess();
	//	void messageDispatcher();
	//	void onConnect();	
		
	private:
		message _payload;
		
		unsigned char _command;
		int _readByteCount;			 //��ȡ�ֽ���������ͷ��
		int _payloadLen;				
		int _remainLen;				 //ʣ��δ��ȡpayload����
		int _remainLenSectionCount; //mqttͷ��ʣ�೤��ָʾλ��ռ�ֽ�����Э��涨<=4
		phase _phase;
		
	};
}
#endif