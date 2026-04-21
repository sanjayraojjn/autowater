import { Component, useState, useEffect } from "react";
import { FlatList, SafeAreaView, View, Text, TouchableOpacity, Image, ActivityIndicator, Alert } from "react-native";
import * as Network from "expo-network";

import { console_log, emulator, esp32_available, num_ips, start_ip } from "./global";
import { styles } from "./SearchingDevices.style"
import { is_device_registered, add_device } from "./devices/storage";
import { device_name } from "./devices/devices";

export default function SerchingDevices(props) {

    const [devices, setDevices] = useState([]);
    //const [loading, setLoading] = useState(true);

    const _populateDevices = (ip_address: string | null) => {
        /**
         * populate list of devices as soon as they are found
        **/
        if(!esp32_available){
            setDevices([{"name": "esp32demo", "ip": "192.168.1.61", "mac":"ma-ca-dd-re-ss-xx", "device_type": "this is an autowater device"}]);
        }
        else{
            //free up device list
            setDevices([]);
            //split ip address
            let octets: string[] = ip_address.split(".", 4);

            let start_ip:number = 1;
            let end_ip:number = 255;
    
            if(emulator){
                start_ip = Number(octets[3]);
                end_ip = start_ip + num_ips;
            }
    
            for(let octet:number=start_ip; octet<end_ip; octet++){
                octets[3] = octet.toString();
                let device_ip = octets.join(".");
                let uri: string = "http://" + device_ip + "/srao_autowater";
                console_log("querying " + device_ip + "--->" + ip_address);
                //console.log("querying " + device_ip + "--->" + ip_address);
    
                //hit the api and check if the device is the one which we are looking for
                fetch(uri)
                .then((response)=>{
                    if(response.ok){
                        response.json().then((res_json)=>{
                            if(res_json.device_type && res_json.device_type === "this is an autowater device"){
                                console_log("number of autowater devices: " + devices.length );

                                //mark the device registered
                                res_json.registered = is_device_registered( device_name(res_json) ) ? true : false;
                                
                                devices.push(res_json);
                                console_log("autowater device " + res_json.name + " found " + res_json);
                                setDevices(devices);
                            }
                        });
                    }
                    else{
                        console_log(device_ip + " returned with " + response.status + ":" + response.statusText);
                    }
                    //return response.json();
                })
                .catch((error)=>{                
                    console.error("error in fetching request from " + device_ip);
                });
            }
        }
    }

    const ItemIcon = (item) => {
        /**
         * layout device icon as per the status of the device's registration on app
        **/
        //check if the device is registered 
        let registered = false;

        if( item.registered ){
            return <Image source={require("../assets/icons/esp32_reg.png")} style={styles.deviceicon} />
        }
        else{
            return <Image source={require("../assets/icons/esp32_regnot.png") } style={styles.deviceicon} />
        }
    }

    const ItemActions = (item) => {
        /**
         * layout actions available with the device as per the status of device
        **/
        if( item.registered ){
            return ( <View style={styles.actioninfo}>
                        <TouchableOpacity onPress={() => handle_open_device(item)} >
                            <Image source={require("../assets/icons/esp32_open.png") } style={styles.actionicon} />
                        </TouchableOpacity>                        
                    </View> )
        }
        else{
            return ( <View style={styles.actioninfo}>
                        <TouchableOpacity onPress={() => handle_add_device(item)} >
                            <Image source={require("../assets/icons/esp32_add.png") } style={styles.actionicon} />
                        </TouchableOpacity>
                    </View> )
        }

    }

    const populateDevices = async () =>{
        let ip_address: string = start_ip;
        if(!emulator){
            //let ip_address_pro = Network.getIpAddressAsync();
            //ip_address = ip_address_pro();
            ip_address = await Network.getIpAddressAsync();
        }
        await _populateDevices(ip_address);
    }
    
    /*
    const populateDevices = async () => {
        let ip_address:string = "192.168.1.1";
        Network.getIpAddressAsync().then( (ipp) =>{
            let octets: string[] = ip_address.split(".", 4);
            for(let octet:number=1; octet<255; octet++){
                octets[3] = octet.toString();
                let device_ip = octets.join(".");
                let uri: string = "http://" + device_ip + "/srao_autowater";
                //console_log("querying " + device_ip);
                console.log("querying " + device_ip + "--->" + ipp);

                //hit the api and check if the device is the one which we are looking for
                fetch(uri)
                .then((response)=>{
                    if(response.ok){
                        response.json().then((res_json)=>{
                            if(res_json.device_type && res_json.device_type === "this is an autowater device"){
                                devices.push(res_json);
                                //console_log("autowater device " + res_json.name + " found");
                                setDevices(devices);
                            }
                        });
                    }
                    else{
                        //console_log(device_ip + " returned with " + response.status + ":" + response.statusText);
                    }
                    //return response.json();
                })
                //.then()
            }
        });
        return devices;
    }
    */

   
    useEffect(() => {
        populateDevices();
        //setLoading(false);
     }, [])
     
    const Item = ({ item }) => (
        <View style={{ flex: 1 }}>
        
            <View style={styles.deviceinfo}>
                <Text style={styles.devicename} >{item.name}</Text>
                <ItemActions item={item} />
            </View>

            <View style={styles.deviceinfo}>
                <Text style={styles.macaddress}>{item.mac}</Text>
                <Text style={styles.ipaddress}>{item.ip}</Text>
            </View>
        </View>
    );

    const renderHeader = () => (
        <View style={styles.header}>
          <Text style={styles.headertitle}>My Devices</Text>
        </View>
      );

    const renderItem = ({ item, index }) => (
       //<TouchableOpacity onPress={() =>navigation.navigate('DetailScreen', item)}>
       //<TouchableOpacity onPress={() => open_details(item, index)} style={styles.listitem}>
        <View style={styles.listitem}>
         <ItemIcon item={item}/>
         <Item item={item}/>
        </View>
        //</TouchableOpacity>
     );

     const handle_open_device = ({item}) => {

     }
     const handle_delete_device = ({item}) => {

     }
     const handle_add_device = async ({item}) => {
        let success: boolean = await add_device( device_name(item), item );
        add_device( device_name(item), item ).then( (added) =>{
            if(!added){
                Alert.alert("Add Device", "Unable to add the device.", [{"text":"OK"}])
            }
            else{
                item.registered = true;
                setDevices(devices);
            }
        } );
     }

    //{ this.loading && <ActivityIndicator size="large" /> }


    return (
        <SafeAreaView  style={styles.container}>
            <FlatList
                data={devices}
                renderItem={renderItem}
                ListHeaderComponent={renderHeader}
                keyExtractor={item => item.ip}
                showsVerticalScrollIndicator={false} />
        </SafeAreaView>
    );
}
