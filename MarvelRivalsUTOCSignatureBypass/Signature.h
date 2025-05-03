#pragma once

// Signature scan in specified memory region
extern void* sigScan(const char* signature, const char* mask, size_t sigSize, void* memory, size_t memorySize);

// Signature scan in current process
extern void* sigScan(const char* signature, const char* mask, void* hint = nullptr);

extern uint64_t GetCurrentBaseAddress(void);

extern void hexDump(const char* description, void* address, u32 length);

extern void* CalculateAddressFromGhidraAddress(uint64_t address);

extern u64 GetAddressFromGlobalRef(u64 a1);
extern u64 GetAddressFromFuncCall(u64 a1);
extern u64 GetAddressFromMOV(u64 a1);