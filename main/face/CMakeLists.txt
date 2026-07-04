idf_component_register(
    SRCS
        "application.cc"
        "face/wajah.cpp"     # <-- WAJIB TAMBAHKAN BARIS INI!
        # ... file cc/cpp lainnya ...
    INCLUDE_DIRS
        "."
        "face"              # <-- Tambahkan juga folder face ke include dir jika diperlukan
    REQUIRES
        arduino
)
