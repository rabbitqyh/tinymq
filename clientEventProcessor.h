#ifndef _CLIENTEVENTPROCESSER_H_
#define _CLIENTEVENTPROCESSER_H_
namespace tinymq{

	enum phase
	{
		FIXHD_BEGIN,
		FIXHD_REMAIN_LENGTH,
		PAYLOAD
	};
	class clientEventProcessor : public eventProcessor
	{
	public:
		clientEventProcessor(tinySocket *tSock);
		~clientEventProcessor();
		 void handleReadEvent();
		 void handleWriteEvent();
		 int getSocketHandle();
		
	private:
		void closeAndClearClient();
		int fixedHeaderProcess();
		int variableHeaderProcess();
		
	private:
		void messageDispatcher();	
		void onConnect();
		void onPublish();
		void onPubAck();
		void onPubRec();
		void onPubRel();
		void onPubComp();
		void onSubscribe();
		void onUnsubscarube();
		void onPingRsp();
		void onDisconnect();
		
	private:
		void * _payload;
		char _command;
		int _readByteCount;			 //��ȡ�ֽ���������ͷ��
		int _payloadLen;				
		int _remaining_length;				 
		int _remaining_mult;
		int _remainLenSectionCount; //mqttͷ��ʣ�೤��ָʾλ��ռ�ֽ�����Э��涨<=4
		phase _nextPhase;
		
	};
}
#endif
