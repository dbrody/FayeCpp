/*
 *   Copyright 2014 Kulykov Oleh
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */


#ifndef __FAYECPP_FAYECPP_H__
#define __FAYECPP_FAYECPP_H__


#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <string>
#include <vector>
#include <list>
#include <map>


#if ( (!defined(__RE_OS_WINDOWS__)) && (!defined(__RE_OS_IPHONE__)) && (!defined(__RE_OS_MACOSX__)) && (!defined(__RE_OS_LINUX__)) && (!defined(__RE_OS_ANDROID__)) && (!defined(__RE_OS_BADA__)) )
/* No manualy selected, try to auto select */

#if (defined(WIN32) || defined(_WIN32) || defined(WIN32_LEAN_AND_MEAN) || defined(_WIN64) || defined(WIN64))

#define __RE_OS_WINDOWS__ 1


#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN /* Exclude rarely-used stuff from Windows headers */
#endif /* WIN32_LEAN_AND_MEAN */


#endif /* END CHECKING WINDOWS PLATFORM  */
/***********************************************************************************/

#endif


#ifndef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif


#ifndef MAX
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#endif


/**
 @brief 8 bit unsigned byte type.
 @detailed 8 bit unsigned byte with 1 byte size.
 */
typedef uint8_t REUByte;


/**
 @brief 16 bit unsigned integer type.
 @detailed 16 bit unsigned integer with 2 byte size.
 */
typedef uint16_t REUInt16;


/**
 @brief 32 bit unsigned integer type.
 @detailed 32 bit unsigned integer with 4 byte size.
 */
typedef uint32_t REUInt32;


/**
 @brief 64 bit unsigned integer type.
 @detailed 64 bit unsigned integer with 8 byte size.
 */
typedef uint64_t REUInt64;


/**
 @brief 8 bit signed byte type.
 @detailed 8 bit signed byte with 1 byte size.
 */
typedef int8_t REByte;


/**
 @brief 16 bit signed integer type.
 @detailed 16 bit signed integer with 2 byte size.
 */
typedef int16_t REInt16;


/**
 @brief 32 bit signed integer type.
 @detailed 32 bit signed integer with 4 byte size.
 */
typedef int32_t REInt32;


/**
 @brief 64 bit signed integer type.
 @detailed 64 bit signed integer with 8 byte size.
 */
typedef int64_t REInt64;


/**
 @brief unsigned identifier integer type.
 @detailed unsigned identifier integer type size is same as pointer.
 */
typedef uintptr_t REUIdentifier;


/**
 @brief Boolean type.
 @detailed Boolean type with possible values: 'true' or 'false'
 */
typedef bool REBOOL;



#if defined(SIZEOF_FLOAT_T)
/**
 @brief 32 bit float type.
 @detailed 32 bit float type with 4 byte size.
 */
typedef float_t REFloat32;
#else
/**
 @brief 32 bit float type.
 @detailed 32 bit float type with 4 byte size.
 */
typedef float REFloat32;
#endif


#if defined(SIZEOF_DOUBLE_T)
/**
 @brief 64 bit float type.
 @detailed 64 bit float type with 8 byte size.
 */
typedef double_t REFloat64;
#else
/**
 @brief 64 bit float type.
 @detailed 64 bit float type with 8 byte size.
 */
typedef double REFloat64;
#endif

/**
 @brief Time interval type.
 @detailed Time interval type with 8 byte size. Used for holding seconds with fractional part
 */
typedef REFloat64 RETimeInterval;


#if !defined(HAVE_SUITABLE_QT_VERSION) && defined(QT_VERSION) && defined(QT_VERSION_CHECK)

#if (QT_VERSION >= QT_VERSION_CHECK(5, 3, 0))
#define HAVE_SUITABLE_QT_VERSION 1
#endif

#endif


#ifdef HAVE_SUITABLE_QT_VERSION
#include <QDebug>
#ifdef DEBUG
#define DEBUG_QT 1
#endif
#endif


namespace FayeCpp {

	class Client;
	class Message;
	class Variant;

	class Delegate
	{
	public:
		/**
		 @brief Client transport protocol connected to server.
		 @param client Faye client object.
		 */
		virtual void onFayeTransportConnected(FayeCpp::Client * client) = 0;


		/**
		 @brief Client transport protocol disconnected from server.
		 @param client Faye client object.
		 */
		virtual void onFayeTransportDisconnected(FayeCpp::Client * client) = 0;


		/**
		 @brief Faye client connected to faye server.
		 @param client Faye client object.
		 */
		virtual void onFayeClientConnected(FayeCpp::Client * client) = 0;


		/**
		 @brief Faye client disconnected to faye server.
		 @param client Faye client object.
		 */
		virtual void onFayeClientDisconnected(FayeCpp::Client * client) = 0;


		/**
		 @brief Faye clent subscribed to channel.
		 @param client Faye client object.
		 @param channel Channel name.
		 */
		virtual void onFayeClientSubscribedToChannel(FayeCpp::Client * client, const std::string & channel) = 0;


		/**
		 @brief Faye clent unsubscribed from channel.
		 @param client Faye client object.
		 @param channel Target channel name.
		 */
		virtual void onFayeClientUnsubscribedFromChannel(FayeCpp::Client * client, const std::string & channel) = 0;


		/**
		 @brief Called when faye client received non empty data from server responce using subscribed channel.
		 @param client Faye client object.
		 @param data Received non empty responce data.
		 @param channel Subscribed channel which received message data.
		 */
		virtual void onFayeClientReceivedDataFromChannel(FayeCpp::Client * client, const std::vector<unsigned char> & data, const std::string & channel) = 0;


		/**
		 @brief Called before message will be sended. You can modify this message if needed.
		 @param client Faye client object.
		 @param message Message object.
		 */
		virtual void onFayeClientWillSendMessage(FayeCpp::Client * client, FayeCpp::Message * message) = 0;


		/**
		 @brief Called before message will be processed by the client object.
		 @param client Faye client object.
		 @param message Message object.
		 */
		virtual void onFayeClientWillReceiveMessage(FayeCpp::Client * client, FayeCpp::Message * message) = 0;


		/**
		 @brief Called on faye client or transport error.
		 @param client Faye client object.
		 @param errorString Readable error string.
		 */
		virtual void onFayeErrorString(FayeCpp::Client * client, const std::string & errorString) = 0;


		virtual ~Delegate() { }
	};



	class Transport;

	class Client
	{
	private:
		Transport * _transport;
		Delegate * _delegate;
		std::string _clientId;

		std::list<std::string> _subscribedChannels;
		std::list<std::string> _pendingSubscriptions;
		std::list<std::string> _supportedConnectionTypes;

		bool _isFayeConnected;

		void processMessage(Message * message);

		void onTransportConnected(Message * message);
		void onTransportDisconnected(Message * message);

		void onClientMessageReceived(Message * message);

		void onClientError(Message * message);

		void onHandshakeDone(Message * message);
		void handshake();

		void onConnectFayeDone(Message * message);
		void connectFaye();

		void onSubscriptionDone(Message * message);
		void subscribePendingSubscriptions();

		void onUnsubscribingDone(Message * message);
		void onDisconnectFayeDone(Message * message);

		static unsigned long long _messageId;
		static unsigned long long nextMessageId();

	public:
		/**
		 @return List of subscribed channels.
		 */
		const std::list<std::string> & subscribedChannels() const;


		/**
		 @return List of supported connection names. Based on server responce(handshake) and on implemented types.
		 */
		const std::list<std::string> & supportedTransportNames() const;


		/**
		 @return Currently connected transport protocol connection type.
		 */
		std::string currentTransportName() const;


		/**
		 @brief Getter for client delegate.
		 @return Pointer to faye client delegate.
		 */
		Delegate * delegate();


		/**
		 @brief Setter for client delegate.
		 */
		void setDelegate(Delegate * delegate);


		/**
		 @brief Getter for faye client id. Returned from the server on handshe step.
		 */
		const std::string & clientId() const;


		/**
		 @brief Getter for faye url.
		 */
		const std::string & url() const;


		/**
		 @brief Setter for faye url.
		 @param url Faye server url string.
		 */
		void setUrl(const std::string & url);


		/**
		 @brief Start connection sequence. On the first step connecting transport protocol to server(inform delegate).
		 @brief Next - connecting faye(also, inform delegate).
		 @return True if sequence initialized, otherwice false.
		 */
		bool connect();


		/**
		 @brief Check connection of the transport protocol.
		 @return True - connected, otherwice false.
		 */
		bool isTransportConnected() const;


		/**
		 @brief Check faye client connection.
		 @return True - connected, otherwice false.
		 */
		bool isFayeConnected() const;


		/**
		 @brief Disconnects from faye server. Transport protocol could be still opened/connected.
		 */
		void disconnect();


		/**
		 @brief Start send message to subscribed channel via connected faye.
		 @param message Non empty message for send.
		 @param channel Non empty, subscribed channel.
		 @return True - if connected and parameters non empty and sended, othervice false.
		 */
		bool sendMessageToChannel(const std::map<std::string, Variant> & message, const std::string & channel);


		/**
		 @brief Check channel is subscribed.
		 @param channel Non empty channel.
		 @return True - if subscribed, otherwice false.
		 */
		bool isSubscribedToChannel(const std::string & channel) const;


		/**
		 * @brief Subscribes or storing to pendnig subscriptions required channel.
		 * @param channel Non empty channel.
		 * @return True - if already suscribed, started or stored to peding subscriptions, otherwice false.
		 */
		bool subscribeToChannel(const std::string & channel);


		/**
		 @brief Unsubscribe from specific channel.
		 @param channel Non empty subscribed channel.
		 @return True on unsubscription started, otherwice false or channel is empty or not subscribed.
		 */
		bool unsubscribeFromChannel(const std::string & channel);


		/**
		 @brief Unsubscribe from all subscribed channels. Also cleanup pending subscriptions.
		 */
		void unsubscribeAllChannels();


		Client();
		virtual ~Client();


		/**
		 * @brief List with implemented/available connection types.
		 * @return Type strings list.
		 */
		static std::list<std::string> availableConnectionTypes();
	};


	/**
	 @brief Type of Faye channel
	 */
	typedef enum _channelType
	{
		/**
		 @brief Undefined Faye channel
		 */
		ChannelTypeNone = 0,


		/**
		 @brief Handshake Faye channel
		 */
		ChannelTypeHandshake,


		/**
		 @brief Connect Faye channel
		 */
		ChannelTypeConnect,


		/**
		 @brief Disconnect Faye channel
		 */
		ChannelTypeDisconnect,


		/**
		 @brief Subscribe Faye channel
		 */
		ChannelTypeSubscribe,


		/**
		 @brief Unsubscribe Faye channel
		 */
		ChannelTypeUnsubscribe
	}
	/**
	 @brief Type of Faye channel
	 */
	ChannelType;



	/**
	 @brief Faye message type.
	 */
	typedef enum _messageType
	{
		/**
		 @brief Undefined, default type.
		 */
		MessageTypeNone = 0,


		/**
		 @brief Faye transport protocol connected to server.
		 */
		MessageTypeTransportConnected,


		/**
		 @brief Faye transport protocol disconnected from server.
		 */
		MessageTypeTransportDisconnected,


		/**
		 @brief Faye transport protocol error.
		 */
		MessageTypeTransportError,


		/**
		 @brief Faye transport protocol received message.
		 */
		MessageTypeServerResponce
	}
	/**
	 @brief Faye message type.
	 */
	MessageType;


	/**
	 @brief Message class for internal logic communication.
	 */
	class Message
	{
	private:
		std::string _clientId;
		std::string _channel;
		std::string _subscription;
		std::string _errorString;
		std::string _version;
		std::string _minimumVersion;
		std::string _connectionType;
		std::list<std::string> _connectionTypes;
		std::vector<unsigned char> _data;
		MessageType _type;
		bool _isSuccessfully;

		void fromJsonDataBuff(const char * jsonData, const size_t dataSize);
		char * jsonString() const;

	public:
		/**
		 @brief Getter for message type.
		 @return Enum type.
		 */
		MessageType type() const;


		/**
		 @brief Getter for client ID.
		 @return Std string with client ID.
		 */
		const std::string & clientId() const;


		/**
		 @brief Getter for channel.
		 @return Std string with channel name.
		 */
		const std::string & channel() const;


		/**
		 @brief Getter for channel type.
		 @return Enum type.
		 */
		ChannelType channelType() const;


		/**
		 @brief Getter for subscription.
		 @return Std string with subscription.
		 */
		const std::string & subscription() const;


		/**
		 @brief Getter for error string.
		 @return Std string with error.
		 */
		const std::string & errorString() const;


		/**
		 @brief Getter for success flag.
		 @return Boolen value of success.
		 */
		bool isSuccessfully() const;


		/**
		 @brief Getter for version string.
		 @return Std string with version.
		 */
		const std::string & version() const;


		/**
		 @brief Getter for minimum version string.
		 @return Std string with minimum version.
		 */
		const std::string & minimumVersion() const;


		/**
		 @brief Getter for connection type string.
		 @return Std string with connection type.
		 */
		const std::string & connectionType() const;


		/**
		 @brief Getter for list of connection type strings.
		 @return Std list with connection types strings.
		 */
		const std::list<std::string> & connectionTypes() const;


		/**
		 @brief Getter for message data.
		 @return Std vector with message data.
		 */
		const std::vector<unsigned char> & data() const;

		Message & setType(MessageType type);
		Message & setClientId(const std::string & value);
		Message & setChannel(const std::string & value);
		Message & setChannelType(const ChannelType type);
		Message & setSubscription(const std::string & value);
		Message & setSuccessfully(bool value);
		Message & setErrorString(const std::string & value);
		Message & setVersion(const std::string & value);
		Message & addConnectionType(const std::string & connectionType);
		Message & setMinimumVersion(const std::string & value);
		Message & setConnectionType(const std::string & value);

		bool isEmpty() const;
		std::vector<unsigned char> toJsonData() const;
		std::string toJsonString() const;
		Message();
		Message(const std::string & jsonString);
		Message(const std::vector<unsigned char> & jsonData);

		static ChannelType stringToType(const std::string & typeString);
		static std::string typeToString(const ChannelType type);
	};


	class Variant
	{
	public:
		typedef enum _variantType
		{
			TypeNone,
			TypeInteger,
			TypeUnsignedInteger,
			TypeReal,
			TypeBool,
			TypeString,
			TypeMap,
			TypeList
		} VariantType;

	protected:
		typedef union _variantUnion
		{
			int64_t int64Value;
			uint64_t uint64Value;
			double doubleValue;
			bool boolValue;
			void * pointerValue;
		} VariantUnion;

		VariantUnion _u;
		VariantType _t;

		void clean();

	public:
		VariantType type() const;

		int toInt() const;

		int64_t toInt64() const;

		uint64_t toUInt64() const;

		double toDouble() const;

		bool toBool() const;

		Variant & operator=(int v);
		Variant & operator=(float v);
		Variant & operator=(double v);

		Variant & operator=(long long v);
		Variant & operator=(unsigned long long v);
		Variant & operator=(long double v);
		Variant & operator=(bool v);
		Variant & operator=(const std::string & s);
		Variant & operator=(const char * s);

		Variant & operator=(const std::map<std::string, Variant> & m);
		Variant & operator=(const std::list<Variant> & l);

		Variant & operator=(const Variant & v);

		const std::string & string() const;

		const std::map<std::string, Variant> & map() const;

		const std::list<Variant> & list() const;

		std::string & string();

		std::map<std::string, Variant> & map();

		std::list<Variant> & list();

		Variant();

		Variant(int v);
		Variant(float v);
		Variant(double v);
		Variant(long long v);
		Variant(unsigned long long v);
		Variant(long double v);
		Variant(bool v);
		Variant(const char * v);
		Variant(const std::string & v);
		Variant(const std::map<std::string, Variant> & v);
		Variant(const std::list<Variant> & v);
		Variant(const Variant & v);

		~Variant();
	};

}




#endif /* __FAYECPP_VARIANT_H__ */

