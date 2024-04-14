#include <cstdint>
#include <string>
#include <string.h>

#include "buffer.h"

Buffer::Buffer(std::uint32_t bufferSize) : _bufferSize(bufferSize), pBuffer(nullptr), _currentSize(std::uint32_t(0))
{
   pBuffer = new char[bufferSize];
}

Buffer::~Buffer()
{
   delete[] pBuffer;
}	 

void* Buffer::getPointerToBuffer()
{
   return static_cast<void*>(pBuffer);
}

void Buffer::clear()
{
   bzero(pBuffer, _bufferSize);
   _currentSize = std::uint32_t(0);
}

void Buffer::serialize(std::string incomingString)
{
   clear();
   for(std::uint32_t i = std::uint32_t(0); i < incomingString.size(); ++i)
   {
      pBuffer[_currentSize + i] = incomingString[i];
   } 
}

void Buffer::deserialize(std::string & outgoingString)
{ 
   for(std::uint32_t i = std::uint32_t(0); static_cast<std::uint32_t>(pBuffer[i]) != 0; ++i)
   {
      outgoingString += pBuffer[i];
   }
}

std::uint32_t Buffer::getCurrentSize()
{
   return _currentSize;
}

std::uint32_t Buffer::getBufferSize()
{
   return _bufferSize;   
}
 
