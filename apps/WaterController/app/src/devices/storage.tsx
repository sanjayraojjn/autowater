import AsyncStorage from "@react-native-async-storage/async-storage";
import { console_log } from "../global";

const _add_device = (name, device) =>{

}

export const add_device = async (name: string, device: {}) =>{
    try{
        AsyncStorage.getItem('DEVICES').then( (devices_json) => {
            //initialize devices object
            let devices = devices_json != null ? JSON.parse(devices_json) : {};
            devices[name] = device;
    
            let devices_str: string = JSON.stringify(devices);
            AsyncStorage.setItem('DEVICES', devices_str);
            return true;
        } );    
    }catch(e){
        console.error("unable to write information of " + name);
        return false;
    }
}

export const is_device_registered = async (name: string) =>{
    try{
        AsyncStorage.getItem('DEVICES').then( (devices_json) => {
            //initialize devices object
            let devices = devices_json != null ? JSON.parse(devices_json) : {};
            return devices[name] ? true : false;
        } );
    }catch(e){
        console.error("unable to check device status of " + name);
        return false;
    }
}
