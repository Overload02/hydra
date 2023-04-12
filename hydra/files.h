/**
 * @file files.h
 * @author Alvajoy 'Alvajoy123' Asante
 * @brief File system
 * @version 0.1
 *
 * @copyright Copyright (c) 2023
 *
 * 888    888   Y88b   d88P   8888888b.     8888888b.          d8888
 * 888    888    Y88b d88P    888  "Y88b    888   Y88b        d88888
 * 888    888     Y88o88P     888    888    888    888       d88P888
 * 8888888888      Y888P      888    888    888   d88P      d88P 888
 * 888    888       888       888    888    8888888P"      d88P  888
 * 888    888       888       888    888    888 T88b      d88P   888
 * 888    888       888       888  .d88P    888  T88b    d8888888888
 * 888    888       888       8888888P"     888   T88b  d88P     888
 * 
 * BSD 3-Clause License
 * Copyright (c) 2023, Alvajoy 'Alvajoy123' Asante.
 * All rights reserved.
 *
 * 	Redistribution and use in source and binary forms, with or without
 *	modification, are permitted provided that the following conditions are met:
 *
 *	Redistributions of source code must retain the above copyright notice, this
 *	list of conditions and the following disclaimer.
 *
 * 	Redistributions in binary form must reproduce the above copyright notice,
 *	this list of conditions and the following disclaimer in the documentation
 *	and/or other materials provided with the distribution.
 *
 * 	Neither the name of the copyright holder nor the names of its
 * 	contributors may be used to endorse or promote products derived from
 * 	this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef hydra_FILES_H
#define hydra_FILES_H

#define HYDRA_NUM_FOLDERS hydra_file_system.numfolders
#define HYDRA_NUM_FILES hydra_file_system.numfiles
#define HYDRA_NUM_PINS hydra_file_system.numpins

#include <tice.h>
#include <graphx.h>

#include "users.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
    /**
     * @brief Enum of hydra file types
     *
     */
    enum hydra_file_type_t
    {
        HYDRA_BASIC_TYPE,
        HYDRA_PBASIC_TYPE,
        HYDRA_ICES_TYPE,
        HYRA_ICE_TYPE,
        HYDRA_C_TYPE,
        HYDRA_ASM_TYPE,
        HYDRA_APPVAR_TYPE,
        HYDRA_ERROR_TYPE,
    };

    /**
     * @brief File System Struct.
     */
    struct hydra_files_t
    {
        uint8_t user_id[HYDRA_MAX_USERS];

        char name[9];
        uint8_t type;

        gfx_sprite_t *icon;
        char *description;
        uint16_t size;

        bool archived;
        bool locked;
        bool hidden;

        struct hydra_folders_t *location[HYDRA_MAX_USERS];
        bool pinned[HYDRA_MAX_USERS];
    };
    extern struct hydra_files_t *hydra_file;

    /**
     * @brief Folder tree struct.
     */
    struct hydra_folders_t
    {
        uint8_t user_id;

        char name[9];
        gfx_sprite_t *icon;

        bool locked;

        struct hydra_folders_t *location;

        bool pinned;
    };
    extern struct hydra_folders_t *hydra_folder;

    /**
     * @brief File system information
     */
    struct hydra_file_system_t
    {
        int numfiles;
        int numfolders;
        int numpins;
    };
    extern struct hydra_file_system_t hydra_file_system;

    /**
     * @brief Init the file system for use.
     */
    void hydra_InitFilesSystem(void);

    /**
     * @brief Searches for a file and returns it's pointer
     *
     * @param name name of the file
     * @param location pointer to the folder location can be NULL for home folder
     * @return struct hydra_files_t* if NULL many issues could have happened (either folder was not found or the was no initialization)
     */
    struct hydra_files_t *SearchFile(char *name, struct hydra_folders_t *location);

    /**
     * @brief Searches for the folder and returns it's pointer
     *
     * @param name name of the folder
     * @param location pointer to the folder location can be NULL for home folder
     * @return struct hydra_folders_t* if NULL many issues could have happened (either folder was not found or the was no initialization)
     */
    struct hydra_folders_t *SearchFolder(char *name, struct hydra_folders_t *location);

    /**
     * @brief Check through file system and removes any files that don't belong.
     *
     */
    void hydra_CheckFileSystem(void);

    /**
     * @brief Rescan the file system to check for new files.
     *
     */
    void hydra_RescanFileSystem(void);

    /**
     * @brief Detects all files on calculator (programs and app-vars).
     */
    void hydra_DetectAllFiles(void);

    /* Deleting folders and files */

    /**
     * @brief Deletes a folder
     *
     * @param folder pointer to the folder you want to delete
     * @return true folder and all it's contents were removed
     * @return false folder and all of it's contents were not removed
     */
    bool hydra_DeleteFolder(struct hydra_folders_t *folder);

    /**
     * @brief Deletes a file
     *
     * @param file pointer to the file toy want to delete
     * @param forceDelete do you want to delete file regardless of other owners?
     */
    bool hydra_DeleteFile(struct hydra_files_t *file);

    /* Creating folders and files */
    /**
     * @brief Adds a file at the given folder position
     *
     * @param name Name of the file you want to create
     * @param location point to the folder you want to store the file in
     * @return struct hydra_files_t* points to the pointer of the file
     */
    struct hydra_files_t *hydra_AddFile(char *name, struct hydra_folders_t *location);

    /**
     * @brief Adds a folder at the given folder postion
     *
     * @param name Name of the folder you want to create
     * @param location pointer to the folder you want to store the folder
     * @return struct hydra_folders_t* points to the new folder just created
     */
    struct hydra_folders_t *hydra_AddFolder(char *name, struct hydra_folders_t *location);

    /* Detecting files icons */
    /**
     * @brief Gets Asm Icon and stores into file pointer.
     */
    void hydra_GetAsmIcons(void);

    /**
     * @brief Gets Basic Icon and stores into file pointer.
     */
    void hydra_GetBasicIcons(void);

    /* Sorting all files */
    /**
     * @brief Sorts all folders Alphabetically.
     */
    void hydra_SortFolders(void);

    /**
     * @brief Sorts all files Alphabetically.
     */
    void hydra_SortFiles(void);

    /**
     * @brief Returns the TI(os) file type
     *
     * @param type Hydra file type
     * @return uint8_t Ti(os) file type
     */
    uint8_t hydra_GetFileType(enum hydra_file_type_t type);

    /* Other */
    /**
     * @brief Opens an editor
     *
     * @param prog_name name of program you want to edit
     * @param editor_name name of editor can be NULL
     * @param callback
     */
    int hydra_EditProgram(struct hydra_files_t *file, const char *editor_name, os_runprgm_callback_t callback);

    /**
     * @brief Run a program
     *
     * @param file pointer to the file
     * @param callback
     */
    int hydra_RunProgram(struct hydra_files_t *file, os_runprgm_callback_t callback);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __hydra_FILES_H__ */