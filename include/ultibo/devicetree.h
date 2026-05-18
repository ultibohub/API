/*
 * This file is part of the Ultibo project, https://ultibo.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2026 Garry Wood <garry@softoz.com.au>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef _ULTIBO_DEVICETREE_H
#define _ULTIBO_DEVICETREE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ultibo/globaltypes.h"
#include "ultibo/globalconst.h"
#include "ultibo/platform.h"

/** Device Tree specific constants */
/** DTB Signature */
#define DTB_MAGIC	0xD00DFEED

/** DTB Versions */
#define DTB_VERSION_17	17
#define DTB_VERSION_16	16

#define DTB_VERSION_CURRENT	DTB_VERSION_17
#define DTB_VERSION_COMPATIBLE	DTB_VERSION_16

/** DTB Tokens */
#define DTB_BEGIN_NODE	0x00000001 ///< The FDT_BEGIN_NODE token marks the beginning of a node’s representation, followed by the node’s unit name as extra data
#define DTB_END_NODE	0x00000002 ///< The FDT_END_NODE token marks the end of a node’s representation
#define DTB_PROP	0x00000003 ///< The FDT_PROP token marks the beginning of the representation of one property, followed by extra data describing the property
#define DTB_NOP	0x00000004 ///< The FDT_NOP token will be ignored by any program parsing the device tree
#define DTB_END	0x00000009 ///< The FDT_END token marks the end of the structure block

/** DTB Offsets */
#define DTB_NODE_OFFSET	4 ///< Token
#define DTB_PROPERTY_OFFSET	12 ///< Token + Value Length + Name Offset

/** DTB Alignment */
#define DTB_STRUCTURE_ALIGNMENT	4
#define DTB_RESERVATION_ALIGNMENT	8

/** DTB Nodes */
/** Standard Nodes */
#define DTB_NODE_ROOT	"/"
#define DTB_NODE_CPUS	"cpus"
#define DTB_NODE_MEMORY	"memory"
#define DTB_NODE_CHOSEN	"chosen"
#define DTB_NODE_ALIASES	"aliases"
/** Other Nodes */
#define DTB_NODE_SYMBOLS	"__symbols__"
#define DTB_NODE_OVERRIDES	"__overrides__"

/** DTB Paths */
#define DTB_PATH_SEPARATOR	"/"

/** DTB Types */
#define DTB_TYPE_UNKNOWN	0
#define DTB_TYPE_EMPTY	1 ///< Value is empty. Used for conveying true-false information
#define DTB_TYPE_U32	2 ///< A 32-bit integer in big-endian format
#define DTB_TYPE_U64	3 ///< Represents a 64-bit integer in big-endian format
#define DTB_TYPE_STRING	4 ///< Strings are printable and null-terminated
#define DTB_TYPE_ENCODED_ARRAY	5 ///< Format is specific to the property. See the property definition
#define DTB_TYPE_PHANDLE	6 ///< A <u32> value. A phandle value is a way to reference another node in the devicetree
#define DTB_TYPE_STRINGLIST	7 ///< A list of <string> values concatenated together

/** DTB Properties */
/** Standard Properties */
#define DTB_PROPERTY_COMPATIBLE	"compatible" ///< The compatible property value consists of one or more strings that define the specific programming model for the device (Type: <stringlist>)
#define DTB_PROPERTY_MODEL	"model" ///< The model property value specifies the manufacturer’s model number of the device (Type: <string>)
#define DTB_PROPERTY_PHANDLE	"phandle" ///< The phandle property specifies a numerical identifier for a node that is unique within the devicetree (Type: <u32>)
#define DTB_PROPERTY_STATUS	"status" ///< The status property indicates the operational status of a device (Type: <string>)
#define DTB_PROPERTY_ADDRESS_CELLS	"#address-cells" ///< Specifies the number of <u32> cells to represent the address in the reg property (Type: <u32>)
#define DTB_PROPERTY_SIZE_CELLS	"#size-cells" ///< Specifies the number of <u32> cells to represent the size in the reg property (Type: <u32>)
#define DTB_PROPERTY_REG	"reg" ///< The reg property describes the address of the device’s resources within the address space defined by its parent bus (Type: <prop-encoded-array>)
#define DTB_PROPERTY_VIRTUAL_REG	"virtual-reg" ///< The virtual-reg property specifies an effective address that maps to the first physical address specified in the reg property of the device node (Type: <u32>)
#define DTB_PROPERTY_RANGES	"ranges" ///< The ranges property provides a means of defining a mapping or translation between address spaces (Type: <empty> or <prop-encoded-array>)
#define DTB_PROPERTY_DMA_RANGES	"dma-ranges" ///< The dma-ranges property is used to describe the direct memory access (DMA) structure of a memory-mapped bus (Type: <empty> or <prop-encoded-array>)
#define DTB_PROPERTY_NAME	"name" ///< The name property is a string specifying the name of the node (Type: <string>)
#define DTB_PROPERTY_DEVICE_TYPE	"device_type" ///< The device_type property was used in IEEE 1275 to describe the device (Type: <string>)

/** Additional Properties for Interrupt Generating Devices */
#define DTB_PROPERTY_INTERRUPTS	"interrupts" ///< The interrupts property defines the interrupt or interrupts that are generated by the device (Type: <prop-encoded-array>)
#define DTB_PROPERTY_INTERRUPT_PARENT	"interrupt-parent" ///< The interrupt-parent property provides an explicit definition of an interrupt parent (Type: <phandle>)
#define DTB_PROPERTY_INTERRUPTS_EXTENDED	"interrupts-extended" ///< The interrupts-extended property lists the interrupt(s) generated by a device (Type: <phandle> <prop-encoded-array>)

/** Additional Properties for Interrupt Controllers */
#define DTB_PROPERTY_INTERRUPT_CELLS	"#interrupt-cells" ///< The #interrupt-cells property defines the number of cells required to encode an interrupt specifier for an interrupt domain (Type: <u32>)
#define DTB_PROPERTY_INTERRUPT_CONTROLLER	"interrupt-controller" ///< The presence of an interrupt-controller property defines a node as an interrupt controller node (Type: <empty>)

/** Additional Interrupt Nexus Properties */
#define DTB_PROPERTY_INTERRUPT_MAP	"interrupt-map" ///< An interrupt-map is a property on a nexus node that bridges an interrupt domain to a parent domain (Type: <prop-encoded-array>)
#define DTB_PROPERTY_INTERRUPT_MAP_MASK	"interrupt-map-mask" ///< An interrupt-map-mask property is specified for a nexus node in the interrupt tree (Type: <prop-encoded-array>)

/** Additional Memory Node Properties */
#define DTB_PROPERTY_INITIAL_MAPPED_AREA	"initial-mapped-area" ///< Specifies the address and size of the Initial Mapped Area (Type: <prop-encoded-array>)

/** Additional Chosen Node Properties */
#define DTB_PROPERTY_BOOTARGS	"bootargs" ///< A string that specifies the boot arguments for the client program (Type: <string>>)
#define DTB_PROPERTY_STDOUT_PATH	"stdout-path" ///< A string that specifies the full path to the node representing the device to be used for boot console output (Type: <string>>)
#define DTB_PROPERTY_STDIN_PATH	"stdin-path" ///< A string that specifies the full path to the node representing the device to be used for boot console input (Type: <string>>)
#define DTB_PROPERTY_INITRD_START	"initrd-start" ///< The starting address of the initial ram disk (Type: <u32>)
#define DTB_PROPERTY_INITRD_END	"initrd-end" ///< The ending address of the initial ram disk (Type: <u32>)

/** Additional CPUs Node Properties */
#define DTB_PROPERTY_CLOCK_FREQUENCY	"clock-frequency" ///< Specifies the current clock speed of the CPU in Hertz (Type: <prop-encoded-array>)
#define DTB_PROPERTY_TIMEBASE_FREQUENCY	"timebase-frequency" ///< Specifies the current frequency at which the timebase and decrementer registers are updated (Type: <propencoded-array>)
#define DTB_PROPERTY_ENABLE_METHOD	"enable-method" ///< Describes the method by which a CPU in a disabled state is enabled (Type: <stringlist>)
#define DTB_PROPERTY_CPU_RELEASE_ADDR	"cpu-release-addr" ///< The cpu-release-addr property is required for cpu nodes that have an enable-method property value of "spin-table" (Type: <u64>)

#define DTB_PROPERTY_POWER_ISA_VERSION	"power-isa-version" ///< A string that specifies the numerical portion of the Power ISA version string (Type: <string>)
#define DTB_PROPERTY_CACHE_OP_BLOCK_SIZE	"cache-op-block-size" ///< The block size in bytes upon which cache block instructions operate (Type: <u32>)
#define DTB_PROPERTY_RESERVATION_GRANULE_SIZE	"reservation-granule-size" ///< The reservation granule size supported by this processor in bytes (Type: <u32>)
#define DTB_PROPERTY_MMU_TYPE	"mmu-type" ///< Specifies the CPU’s MMU type (Type: <string>)

#define DTB_PROPERTY_TLB_SPLIT	"tlb-split" ///< Specifies that the TLB has a split configuration (Type: <empty>)
#define DTB_PROPERTY_TLB_SIZE	"tlb-size" ///< Specifies the number of entries in the TLB (Type: <u32>)
#define DTB_PROPERTY_TLB_SETS	"tlb-sets" ///< Specifies the number of associativity sets inthe TLB. (Type: <u32>)
#define DTB_PROPERTY_D_TLB_SIZE	"d-tlb-size" ///< Specifies the number of entries in the data TLB (Type: <u32>)
#define DTB_PROPERTY_D_TLB_SETS	"d-tlb-sets" ///< Specifies the number of associativity sets in the data TLB. (Type: <u32>)
#define DTB_PROPERTY_I_TLB_SIZE	"i-tlb-size" ///< Specifies the number of entries in the instruction TLB (Type: <u32>)
#define DTB_PROPERTY_I_TLB_SETS	"i-tlb-sets" ///< Specifies the number of associativity sets in the instruction TLB (Type: <u32>)

#define DTB_PROPERTY_CACHE_UNIFIED	"cache-unified" ///< Specifies the cache has a unified organization (Type: <empty>)
#define DTB_PROPERTY_CACHE_SIZE	"cache-size" ///< Specifies the size in bytes of a unified cache (Type: <u32>)
#define DTB_PROPERTY_CACHE_SETS	"cache-sets" ///< Specifies the number of associativity sets in a unified cache (Type: <u32>)
#define DTB_PROPERTY_CACHE_BLOCK_SIZE	"cache-block-size" ///< Specifies the block size in bytes of a unified cache (Type: <u32>)
#define DTB_PROPERTY_CACHE_LINE_SIZE	"cache-line-size" ///< Specifies the line size in bytes of a unified cache (Type: <u32>)
#define DTB_PROPERTY_I_CACHE_SIZE	"i-cache-size" ///< Specifies the size in bytes of the instruction cache (Type: <u32>)
#define DTB_PROPERTY_I_CACHE_SETS	"i-cache-sets" ///< Specifies the number of associativity sets in the instruction cache (Type: <u32>)
#define DTB_PROPERTY_I_CACHE_BLOCK_SIZE	"i-cache-block-size" ///< Specifies the block size in bytes of the instruction cache (Type: <u32>)
#define DTB_PROPERTY_I_CACHE_LINE_SIZE	"i-cache-line-size" ///< Specifies the line size in bytes of the instruction cache (Type: <u32>)
#define DTB_PROPERTY_D_CACHE_SIZE	"d-cache-size" ///< Specifies the size in bytes of the data cache (Type: <u32>)
#define DTB_PROPERTY_D_CACHE_SETS	"d-cache-sets" ///< Specifies the number of associativity sets in the data cache. (Type: <u32>)
#define DTB_PROPERTY_D_CACHE_BLOCK_SIZE	"d-cache-block-size" ///< Specifies the block size in bytes of the data cache. (Type: <u32>)
#define DTB_PROPERTY_D_CACHE_LINE_SIZE	"d-cache-line-size" ///< Specifies the line size in bytes of the data cache, (Type: <u32>)
#define DTB_PROPERTY_NEXT_LEVEL_CACHE	"next-level-cache" ///< If present, indicates that another level of cache exists. (Type: <phandle>)

#define DTB_PROPERTY_CACHE_LEVEL	"cache-level" ///< Specifies the level in the cache hierarchy (Type: <u32>)

/** Other Additional Properties */
#define DTB_PROPERTY_SERIAL_NUMBER	"serial-number" ///< Serial Number (Type: <string>)
#define DTB_PROPERTY_ALLOC_RANGES	"alloc-ranges" ///< Allocated Ranges (Type: <prop-encoded-array>)
#define DTB_PROPERTY_RESETS	"resets" ///< Resets (Type: <prop-encoded-array>)
#define DTB_PROPERTY_CLOCK_CELLS	"#clock-cells" ///< Number of clock cells (Type: <u32>)
#define DTB_PROPERTY_LINUX_INITRD_START	"linux,initrd-start" ///< The starting address of the initial ram disk (Type: <u32>)
#define DTB_PROPERTY_LINUX_INITRD_END	"linux,initrd-end" ///< The ending address of the initial ram disk (Type: <u32>)

/** DTB Property Types */
#define DTB_MAX_PROPERTY_TYPE	60

/** Device Tree specific types */
/** DTB Header */
typedef struct _DTB_HEADER DTB_HEADER;
struct _DTB_HEADER
{
	uint32_t magic; ///< The value 0xd00dfeed (big-endian)
	uint32_t totalsize; ///< The total size in bytes of the devicetree data structure (big-endian)
	uint32_t structureoffset; ///< The offset in bytes of the structure block from the beginning of the header (big-endian)
	uint32_t stringsoffset; ///< The offset in bytes of the strings block from the beginning of the header (big-endian)
	uint32_t reservationoffset; ///< The offset in bytes of the memory reservation block from the beginning of the header (big-endian)
	uint32_t version; ///< The version of the devicetree data structure (big-endian)
	uint32_t compatibleversion; ///< The lowest version of the devicetree data structure with which the version used is backwards compatible (big-endian)
	uint32_t bootcpuid; ///< The physical ID of the system’s boot CPU (big-endian)
	uint32_t stringssize; ///< The length in bytes of the strings block section of the devicetree blob (big-endian)
	uint32_t structuresize; ///< The length in bytes of the structure block section of the devicetree blob (big-endian)
} PACKED;

/** DTB Reservation */
typedef struct _DTB_RESERVATION DTB_RESERVATION;
struct _DTB_RESERVATION
{
	uint64_t address; ///< Physical address of a reserved memory region
	uint64_t size; ///< Size in bytes of a reserved memory region
} PACKED;

/** DTB Node */
typedef struct _DTB_NODE DTB_NODE;
struct _DTB_NODE
{
	uint32_t token; ///< Token (big-endian)
	char name[1]; ///< The name stored as a null-terminated string, shall include the unit address if any
} PACKED;

/** DTB Property */
typedef struct _DTB_PROPERTY DTB_PROPERTY;
struct _DTB_PROPERTY
{
	uint32_t token; ///< Token (big-endian)
	uint32_t valuelength; ///< The length of the property value in bytes
	uint32_t nameoffset; ///< The offset into the strings block of the property name stored as a null-terminated string
	uint8_t value[1]; ///< The property value as an array of bytes of value length
} PACKED;


/** DTB Property Char */
typedef struct _DTB_PROPERTY_CHAR DTB_PROPERTY_CHAR;
struct _DTB_PROPERTY_CHAR
{
	uint32_t token; ///< Token (big-endian)
	uint32_t valuelength; ///< The length of the property value in bytes
	uint32_t nameoffset; ///< The offset into the strings block of the property name stored as a null-terminated string
	char value[1]; ///< The property value as a string of value length
} PACKED;


/** DTB Property LongWord */
typedef struct _DTB_PROPERTY_LONGWORD DTB_PROPERTY_LONGWORD;
struct _DTB_PROPERTY_LONGWORD
{
	uint32_t token; ///< Token (big-endian)
	uint32_t valuelength; ///< The length of the property value in bytes
	uint32_t nameoffset; ///< The offset into the strings block of the property name stored as a null-terminated string
	uint32_t value[1]; ///< The property value as an array of longwords of value length (big-endian)
} PACKED;


/** DTB Property QuadWord */
typedef struct _DTB_PROPERTY_QUADWORD DTB_PROPERTY_QUADWORD;
struct _DTB_PROPERTY_QUADWORD
{
	uint32_t token; ///< Token (big-endian)
	uint32_t valuelength; ///< The length of the property value in bytes
	uint32_t nameoffset; ///< The offset into the strings block of the property name stored as a null-terminated string
	uint64_t value[1]; ///< The property value as an array of quadwords of value length (big-endian)
} PACKED;

/** Device Tree Logging specific types */
typedef void STDCALL (*dtb_log_output_cb)(const char *text, void *data);
typedef char * STDCALL (*dtb_decode_value_cb)(HANDLE node, HANDLE handle, void *value, uint32_t size, void *data);

/** Device Tree Functions */

/**
 * @brief Check the data at the supplied address to determine if it is a valid Device Tree Blob
 * @param Address The address to be validated
 * @param Size On return contains the total size of the Device Tree Blob if valid
 * @return True if the address points to a valid Device Tree Blob, False if not
 * @note Does not overwrite passed Size unless the DTB is valid
 */
BOOL STDCALL device_tree_validate(size_t address, uint32_t *size);

/**
 * @brief Find the next DTB node within the Device Tree
 * @param Parent Handle of the parent node to search in, INVALID_HANDLE_VALUE to search the entire tree
 * @param Previous Handle of the node to start from, INVALID_HANDLE_VALUE to start from the root node
 * @return The handle of the next node in the tree or INVALID_HANDLE_VALUE if no node was found
 */
HANDLE STDCALL device_tree_next_node(HANDLE parent, HANDLE previous);

/**
 * @brief Find the next DTB property within the specified node of the Device Tree
 * @param Node Handle of the node to search in
 * @param Previous Handle of the property to start from, INVALID_HANDLE_VALUE to start from the first property
 * @return The handle of the next property in the node or INVALID_HANDLE_VALUE if no property was found
 */
HANDLE STDCALL device_tree_next_property(HANDLE node, HANDLE previous);

/**
 * @brief Get the handle of the node matching the specified path, optionally within a specified parent
 * @param Path The path of the node to find, relative to parent node or fully qualified if parent not specified (eg /chosen or /cpus/cpu0)
 * @param Parent Handle of the parent node to search in, INVALID_HANDLE_VALUE to search the entire tree
 * @return The handle of the node which matches the path or INVALID_HANDLE_VALUE if no node was found
 */
HANDLE STDCALL device_tree_get_node(const char *path, HANDLE parent);

/**
 * @brief Get the handle of the property matching the specified name
 * @param Node Handle of the node to search in
 * @param Name The name of the node to find (eg compatible)
 * @return The handle of the property which matches the name or INVALID_HANDLE_VALUE if no property was found
 */
HANDLE STDCALL device_tree_get_property(HANDLE node, const char *name);

/**
 * @brief Get the name of the specified node
 * @param Handle The handle of the node to get the name of
 * @return The name of the specified node or an empty string if the node was not valid
 */
uint32_t STDCALL device_tree_get_node_name(HANDLE handle, char *name, uint32_t len);

/**
 * @brief Split the name of a node into node name and unit address
 * @param Handle The handle of the node to split the name of
 * @param NodeName The node name on return or an empty string if the node was not valid
 * @param UnitAddress The unit address on return (If applicable)
 */
uint32_t STDCALL device_tree_split_node_name(HANDLE handle, char *nodename, uint32_t namelen, char *unitaddress, uint32_t addresslen);

/**
 * @brief Get the parent node of the specified node
 * @param Handle The handle of the node to get the parent of
 * @return The handle of the parent node or INVALID_HANDLE_VALUE if the node was not valid
 */
HANDLE STDCALL device_tree_get_node_parent(HANDLE handle);

/**
 * @brief Get the #address-cells and #size-cells values that apply to reg properties of the specified node
 * @param Handle The handle of the node to get the cell sizes for
 * @param Address The #address-cells value on return (or the default value if not found)
 * @param Size The #size-cells value on return (or the default value if not found)
 * @return True if the cell sizes were found or False if the node was not valid
 * @note The address and size values applicable to a given node will be those
 *        from a parent node, not those found in the node itself (if present)
 * @note Used by early stage boot stage processing which must limit the use of strings
 *        and other memory allocations. This function uses a memory compare for names
 */
BOOL STDCALL device_tree_get_node_reg_cells(HANDLE handle, uint32_t *address, uint32_t *size);

/**
 * @brief Get the #address-cells and #size-cells values that apply to range properties of the specified node
 * @param Handle The handle of the node to get the cell sizes for
 * @param ParentAddress The #address-cells value from the parent on return (or the default value if not found)
 * @param NodeAddress The #address-cells value from this node on return (or the default value if not found)
 * @param NodeSize The #size-cells value from this node on return (or the default value if not found)
 * @return True if the cell sizes were found or False if the node was not valid
 * @note Range properties use the address value from the parent node and the address and size values
 *        from the node itself to determine the size of each range
 * @note Used by early stage boot stage processing which must limit the use of strings
 *        and other memory allocations. This function uses a memory compare for names
 */
BOOL STDCALL device_tree_get_node_range_cells(HANDLE handle, uint32_t *parentaddress, uint32_t *nodeaddress, uint32_t *nodesize);

/**
 * @brief Get the name of the specified property
 * @param Handle The handle of the property to get the name of
 * @return The name of the specified property or an empty string if the property was not valid
 */
uint32_t STDCALL device_tree_get_property_name(HANDLE handle, char *name, uint32_t len);

/**
 * @brief Split the name of a property into property name and unique prefix
 * @param Handle The handle of the property to split the name of
 * @param UniquePrefix The unique prefix on return (If applicable)
 * @param PropertyName The property name on return or an empty string if the property was not valid
 */
uint32_t STDCALL device_tree_split_property_name(HANDLE handle, char *uniqueprefix, uint32_t prefixlen, char *propertyname, uint32_t namelen);

/**
 * @brief Get a pointer to the raw value of the specified property
 * @param Handle The handle of the property to get the value of
 * @return A pointer to the specified property value or nil if the property was not valid
 * @note The returned value points to the memory block where device tree is stored and should not be modified or freed
 */
void * STDCALL device_tree_get_property_value(HANDLE handle);

/**
 * @brief Get the length of the raw value of the specified property
 * @param Handle The handle of the property to get the value length of
 * @return The length of the specified property value in bytes or -1 if the property was not valid
 */
uint32_t STDCALL device_tree_get_property_length(HANDLE handle);

/**
 * @brief Get the value of the specified property as a string
 * @param Handle The handle of the property to get the value of
 * @return A string representation of the value or an empty string if the property was not valid
 */
uint32_t STDCALL device_tree_get_property_string(HANDLE handle, char *string, uint32_t len);

/**
 * @brief Get the value of the specified property as a longword
 * @param Handle The handle of the property to get the value of
 * @return A longword representation of the value or 0 if the property was not valid
 */
uint32_t STDCALL device_tree_get_property_longword(HANDLE handle);

/**
 * @brief Get the value of the specified property as a quadword
 * @param Handle The handle of the property to get the value of
 * @return A quadword representation of the value or 0 if the property was not valid
 */
uint64_t STDCALL device_tree_get_property_quadword(HANDLE handle);

/** Device Tree Helper Functions */

/**
 * @brief Return a character pointer to the location of the command line in the device tree blob
 * @note Intended primarily for use by early boot stage processing which must limit the use of strings
 *        and other memory allocations. For normal use see DeviceTreeGetNode and DeviceTreeGetProperty
 */
char * STDCALL device_tree_get_boot_args(void);

/**
 * @brief Return the address and size of the initial ram disk specified in the device tree blob
 * @param Address Used to return the address value
 * @param Size Used to return the size value
 * @return True if an initial ram disk was specified in the device tree, False if not
 * @note Intended primarily for use by early boot stage processing which must limit the use of strings
 *        and other memory allocations. For normal use see DeviceTreeGetNode and DeviceTreeGetProperty
 */
BOOL STDCALL device_tree_get_ramdisk(size_t *address, uint64_t *size);

/**
 * @brief Return the address and size of a memory block specified in the device tree blob
 * @param Index The index of the memory block to return (The first block is 0)
 * @param Range Used to return the page range value (If applicable)
 * @param Address Used to return the address value
 * @param Size Used to return the size value
 * @return True if the memory block requested was found in the device tree, False if not
 * @note Intended primarily for use by early boot stage processing which must limit the use of strings
 *        and other memory allocations. For normal use see DeviceTreeGetNode and DeviceTreeGetProperty
 */
#if defined (__i386__) || defined (__arm__)
BOOL STDCALL device_tree_get_memory(uint32_t index, uint32_t *range, size_t *address, uint64_t *size);
#else
BOOL STDCALL device_tree_get_memory(uint32_t index, size_t *address, uint64_t *size);
#endif

/**
 * @brief Return the address and size of a memory reservation specified in the device tree blob
 * @param Index The index of the memory reservation to return (The first reservation is 0)
 * @param Address Used to return the address value
 * @param Size Used to return the size value
 * @return True if the memory reservation requested was found in the device tree, False if not
 */
BOOL STDCALL device_tree_get_reservation(uint32_t index, size_t *address, uint64_t *size);

/**
 * @brief Print information about all nodes and properties in the device tree
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL device_tree_log_tree(void);

/**
 * @brief Print information about one or all nodes and properties in the device tree with custom value decode callback
 * @param Node The node to print information about (INVALID_HANDLE_VALUE for all nodes)
 * @param Output The log output callback to print information to (nil to use the default output)
 * @param Decode The callback to decode a value into a string (nil to use the default decode)
 * @param Data A pointer to caller specific data which should be passed to the callbacks (Optional)
 * @return ERROR_SUCCESS if completed or another error code on failure
 */
uint32_t STDCALL device_tree_log_tree_ex(HANDLE node, dtb_log_output_cb output, dtb_decode_value_cb decode, void *data);

#ifdef __cplusplus
}
#endif

#endif // _ULTIBO_DEVICETREE_H