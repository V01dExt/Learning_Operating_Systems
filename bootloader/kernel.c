void kernel_main() {
    char* video_memory = (char*) 0xB8000;
    
    video_memory[0] = 'W';
    video_memory[1] = 0x07;

    while (1) {

    }
    
}
