export const console_enabled = true;
export const emulator = true;
export const start_ip = "192.168.1.50";
export const num_ips = 20;
export const esp32_available = true;

export const console_log = (args) =>{
    if(console_enabled){
        console.log(args);
    }
}
