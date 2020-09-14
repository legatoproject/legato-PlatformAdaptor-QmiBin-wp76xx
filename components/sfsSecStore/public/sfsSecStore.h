/**
 * @page c_sfsSecStore Legacy Secure Storage Interface
 *
 * This module contains an interface into the legacy SFS-based implementation of
 * secure storage.  This allows upgrade from legacy storage to the new secureStore
 * implementations.
 *
 * <HR>
 *
 * Copyright (C) Sierra Wireless Inc.
 */

#ifndef LEGATO_SFS_SECURE_STORAGE_INCLUDE_GUARD
#define LEGATO_SFS_SECURE_STORAGE_INCLUDE_GUARD

#include "legato.h"

#include "pa_secStore.h"

//--------------------------------------------------------------------------------------------------
/**
 * Writes the data in the buffer to the specified path in secure storage replacing any previously
 * written data at the same path.
 *
 * @return
 *      LE_OK if successful.
 *      LE_NO_MEMORY if there is not enough memory to store the data.
 *      LE_UNAVAILABLE if the secure storage is currently unavailable.
 *      LE_BAD_PARAMETER if the path cannot be written to because it is a directory or it would
 *                       result in an invalid path.
 *      LE_FAULT if there was some other error.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t sfsSecStore_Write
(
    const char* pathPtr,            ///< [IN] Path to write to.
    const uint8_t* bufPtr,          ///< [IN] Buffer containing the data to write.
    size_t bufSize                  ///< [IN] Size of the buffer.
);


//--------------------------------------------------------------------------------------------------
/**
 * Reads data from the specified path in secure storage.
 *
 * @return
 *      LE_OK if successful.
 *      LE_OVERFLOW if the buffer is too small to hold all the data.  No data will be written to the
 *                  buffer in this case.
 *      LE_NOT_FOUND if the path is empty.
 *      LE_UNAVAILABLE if the secure storage is currently unavailable.
 *      LE_FAULT if there was some other error.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t sfsSecStore_Read
(
    const char* pathPtr,            ///< [IN] Path to read from.
    uint8_t* bufPtr,                ///< [OUT] Buffer to store the data in.
    size_t* bufSizePtr              ///< [IN/OUT] Size of buffer when this function is called.
                                    ///          Number of bytes read when this function returns.
);


//--------------------------------------------------------------------------------------------------
/**
 * Write the meta data to the specified path.
 *
 * @return
 *      LE_OK if successful.
 *      LE_NOT_FOUND if the meta data cannot be retrieved.
 *      LE_UNAVAILABLE if the secure storage is currently unavailable.
 *      LE_FAULT if there was some other error.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t sfsSecStore_CopyMetaTo
(
    const char* pathPtr             ///< [IN] Destination path of meta file copy.
);


//--------------------------------------------------------------------------------------------------
/**
 * Deletes the specified path and everything under it.
 *
 * @return
 *      LE_OK if successful.
 *      LE_NOT_FOUND if the path does not exist.
 *      LE_UNAVAILABLE if the secure storage is currently unavailable.
 *      LE_FAULT if there was an error.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t sfsSecStore_Delete
(
    const char* pathPtr             ///< [IN] Path to delete.
);


//--------------------------------------------------------------------------------------------------
/**
 * Gets the size, in bytes, of the data at the specified path and everything under it.
 *
 * @return
 *      LE_OK if successful.
 *      LE_NOT_FOUND if the path does not exist.
 *      LE_UNAVAILABLE if the secure storage is currently unavailable.
 *      LE_FAULT if there was an error.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t sfsSecStore_GetSize
(
    const char* pathPtr,            ///< [IN] Path.
    size_t* sizePtr                 ///< [OUT] Size in bytes of all items in the path.
);


//--------------------------------------------------------------------------------------------------
/**
 * Iterates over all entries under the specified path (non-recursive), calling the supplied callback
 * with each entry name.
 *
 * @return
 *      LE_OK if successful.
 *      LE_UNAVAILABLE if the secure storage is currently unavailable.
 *      LE_FAULT if there was some other error.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t sfsSecStore_GetEntries
(
    const char* pathPtr,                    ///< [IN] Path.
    pa_secStore_GetEntry_t getEntryFunc,    ///< [IN] Callback function to call with each entry.
    void* contextPtr                        ///< [IN] Context to be supplied to the callback.
);


//--------------------------------------------------------------------------------------------------
/**
 * Gets the total space and the available free space in secure storage.
 *
 * @return
 *      LE_OK if successful.
 *      LE_UNAVAILABLE if the secure storage is currently unavailable.
 *      LE_FAULT if there was some other error.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t sfsSecStore_GetTotalSpace
(
    size_t* totalSpacePtr,                  ///< [OUT] Total size, in bytes, of secure storage.
    size_t* freeSizePtr                     ///< [OUT] Free space, in bytes, in secure storage.
);


//--------------------------------------------------------------------------------------------------
/**
 * Copies all the data from source path to destination path.  The destination path must be empty.
 *
 * @return
 *      LE_OK if successful.
 *      LE_UNAVAILABLE if the secure storage is currently unavailable.
 *      LE_FAULT if there was some other error.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t sfsSecStore_Copy
(
    const char* destPathPtr,                ///< [IN] Destination path.
    const char* srcPathPtr                  ///< [IN] Source path.
);


//--------------------------------------------------------------------------------------------------
/**
 * Moves all the data from source path to destination path.  The destination path must be empty.
 *
 * @return
 *      LE_OK if successful.
 *      LE_UNAVAILABLE if the secure storage is currently unavailable.
 *      LE_FAULT if there was some other error.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t sfsSecStore_Move
(
    const char* destPathPtr,                ///< [IN] Destination path.
    const char* srcPathPtr                  ///< [IN] Source path.
);

//--------------------------------------------------------------------------------------------------
/**
 * Re-initialize the secure storage if is already initialized.
 *
 * @note
 *      This should be called each time the NV restore done indication is received in service level,
 *      so that the meta hash can be rebuilt.
 *
 * @return
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED void sfsSecStore_ReInitSecStorage
(
    void
);

//--------------------------------------------------------------------------------------------------
/**
 * This function must be called to register a handler for restore event in PA level to notify
 * service level.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_event_HandlerRef_t sfsSecStore_SetRestoreHandler
(
    pa_secStore_RestoreHdlrFunc_t handlerFuncPtr ///< [IN] The handler function.
);

#endif // LEGATO_PA_SECURE_STORAGE_INCLUDE_GUARD
