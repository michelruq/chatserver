

class Buffer
{
   public:
      Buffer(std::uint32_t bufferSize);
      ~Buffer();

      void* getPointerToBuffer();
      void clear();
      void serialize(std::string incomingString);
      void deserialize(std::string & outgoingString);
      std::uint32_t getCurrentSize();
      std::uint32_t getBufferSize();
      
   private:
      std::uint32_t _bufferSize;
      char* pBuffer;      
      std::uint32_t _currentSize;
};


