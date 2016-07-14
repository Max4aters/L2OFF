
#pragma once

#include <windows.h>
#include <yvals.h>
#include <cstddef>
#include <string>

extern HANDLE server;

void WriteMemoryBYTES(unsigned int uAddress, void* bytes, unsigned int len);
void WriteMemoryQWORD(unsigned int uAddress, unsigned __int64 value);
void WriteMemoryDWORD(unsigned int uAddress, unsigned int value);
void WriteMemoryWORD(unsigned int uAddress, unsigned short value);
void WriteMemoryBYTE(unsigned int uAddress, unsigned char value);
void ReadMemoryBYTES(unsigned int uAddress, void* bytes, unsigned int len);
void WriteAddress(unsigned int uAddress, UINT32 absAddr);
unsigned __int64 ReadMemoryQWORD(unsigned int uAddress);
unsigned int ReadMemoryDWORD(unsigned int uAddress);
unsigned short ReadMemoryWORD(unsigned int uAddress);
unsigned char ReadMemoryBYTE(unsigned int uAddress);
void NOPMemory(unsigned int uAddress, unsigned int len);
void NULLMemory(unsigned int uAddress, unsigned int len);
void WriteInstruction(unsigned int uAddress, unsigned int uDestination, unsigned char uFirstByte);
void WriteInstructionCallJmpEax(unsigned int uAddress, unsigned int uDestination, unsigned int uNopEnd = NULL);
void WriteInstructionCall(unsigned int uAddress, unsigned int uDestination, unsigned int uNopEnd = NULL);
void WriteInstructionJmp(unsigned int uAddress, unsigned int uDestination, unsigned int uNopEnd = NULL);
bool ReplaceString(unsigned int uAddress, const wchar_t *from, const wchar_t *to);

template <typename Type, typename Member, int Offset, int RequiredOffset>
struct MemberOffsetCheck;

template <typename Type, typename Member, int Offset>
struct MemberOffsetCheck<Type, Member, Offset, Offset>
{};

#define CompileTimeOffsetCheck(Type, Member, Offset)								\
	typedef size_t Type##__##Member##__;											\
	struct Type##__##Member##__OffsetCheck :										\
	MemberOffsetCheck<Type, Type##__##Member##__, offsetof(Type, Member), Offset>	\
	{}

typedef int (__cdecl *Assemble_t)(char*, int, const char*, ...);
typedef const unsigned char* (__cdecl *Disassemble_t)(const unsigned char*, const char*, ...);

extern Assemble_t Assemble;
extern Disassemble_t Disassemble;

std::basic_string<wchar_t> Widen(const std::string &s);

class Guard {
public:
	__forceinline Guard(const wchar_t* functionName)
	{
		if (!off1 || !off2 || !off3) return;
		UINT32 threadIndex = *reinterpret_cast<UINT32*>(*reinterpret_cast<UINT64*>(__readgsqword(0x58)) + off1);
		reinterpret_cast<const wchar_t**>(off2)[threadIndex * 1000 + reinterpret_cast<UINT32*>(off3)[threadIndex]++] = functionName;
	}

	__forceinline ~Guard()
	{
		if (!off1 || !off2 || !off3) return;
		UINT32 threadIndex = *reinterpret_cast<UINT32*>(*reinterpret_cast<UINT64*>(__readgsqword(0x58)) + off1);
		--reinterpret_cast<UINT32*>(off3)[threadIndex];
	}

	static size_t off1;
	static size_t off2;
	static size_t off3;
};

#define WIDEN2(x) L##x
#define WIDEN(x) WIDEN2(x)
#define __WFILE__ WIDEN(__FILE__)
#define __WDATE__ WIDEN(__DATE__)
#define __WTIME__ WIDEN(__TIME__)
#define __WFUNCTION__ WIDEN(__FUNCTION__)
#define __WFUNCDNAME__ WIDEN(__FUNCDNAME__)
#define __WFUNCSIG__ WIDEN(__FUNCSIG__)

#define WIDEN2(x) L##x
#define WIDEN(x) WIDEN2(x)
#define GUARDED Guard functionGuard_(__WFUNCSIG__);

