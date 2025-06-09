include("Utils")
include("ExternalsUtils")

# REQUIRES SDL3
block()
    set(lib_name "physfs")
    Announce("Configuring \"${lib_name}\" external library.")

    ForceBool(PHYSFS_ARCHIVE_ZIP ON)         # Enable ZIP archive support
    ForceBool(PHYSFS_ARCHIVE_7Z ON)          # Enable 7zip archive support
    ForceBool(PHYSFS_ARCHIVE_GRP ON)         # Enable Build Engine GRP archive support
    ForceBool(PHYSFS_ARCHIVE_WAD ON)         # Enable Doom WAD archive support
    ForceBool(PHYSFS_ARCHIVE_CSM ON)         # Enable Chasm: The Rift CSM.BIN archive support
    ForceBool(PHYSFS_ARCHIVE_HOG ON)         # Enable Descent I/II HOG archive support
    ForceBool(PHYSFS_ARCHIVE_MVL ON)         # Enable Descent I/II MVL archive support
    ForceBool(PHYSFS_ARCHIVE_QPAK ON)        # Enable Quake I/II QPAK archive support
    ForceBool(PHYSFS_ARCHIVE_SLB ON)         # Enable I-War / Independence War SLB archive support
    ForceBool(PHYSFS_ARCHIVE_ISO9660 ON)     # Enable ISO9660 archive support
    ForceBool(PHYSFS_ARCHIVE_VDF ON)         # Enable Gothic I/II VDF archive support
    ForceBool(PHYSFS_ARCHIVE_LECARCHIVES ON) # Enable LucasArts GOB/LAB/LFD archive support

    ForceBool(PHYSFS_BUILD_STATIC ON)        # Build the static PhysFS library
    ForceBool(PHYSFS_BUILD_SHARED OFF)        # Build the shared PhysFS library
    ForceBool(PHYSFS_BUILD_TEST OFF)          # Build the stdio test program
    ForceBool(PHYSFS_DISABLE_INSTALL ON)      # Disable installing PhysFS
    ForceBool(PHYSFS_BUILD_DOCS OFF)          # Build doxygen-based documentation


    AddExternalSubdirectory(${lib_name})
endblock()
