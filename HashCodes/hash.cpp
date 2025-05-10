std::string fnv1aHash(const std::string& filePath) {
    const uint64_t FNV_PRIME = 0x100000001B3;
    const uint64_t OFFSET_BASIS = 0xCBF29CE484222325;
    uint64_t hash = OFFSET_BASIS;

    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        return "";
    }

    char byte;
    while (file.get(byte)) {
        hash ^= static_cast<unsigned char>(byte);
        hash *= FNV_PRIME;
    }

    file.close();



    //COMPRIMIR EM 15 HEXADECIMAIS//////////////////////////////////////////////////////////
    const uint64_t MASK_60BITS = 0xFFFFFFFFFFFFFFF; // 15 caracteres hexadecimais (60 bits)

    // Aplica uma máscara para garantir que o hash tenha no máximo 60 bits
    uint64_t compressedHash = hash & MASK_60BITS;

    // Se o hash original for maior que 60 bits, "fold" (comprime) o hash
    if (hash > MASK_60BITS) {
        compressedHash ^= (hash >> 60);
    }

    // Converte o hash comprimido para uma string hexadecimal de 15 caracteres
    std::stringstream ss;
    ss << std::hex << std::uppercase << std::setw(15) << std::setfill('0') << compressedHash;



    return ss.str();
    ////////////////////////////////////////////////////////////////////////////////////////
}