idf_component_register(
    SRCS "wajah.cpp"
    INCLUDE_DIRS "."
    REQUIRES arduino  # Pastikan library Arduino terpasang jika menggunakan Adafruit GFX gaya Arduino
)
