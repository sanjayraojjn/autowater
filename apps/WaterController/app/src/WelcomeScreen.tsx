import React from 'react';
import { useState } from 'react';
import { Image } from 'react-native';
import { ImageBackground, StyleSheet, View, Text } from 'react-native';

function WelcomeScreen(props) {
    const [connectText, setConnectText] = useState("Connect");
    const [monitorText, setMonitorText] = useState("Monitor");

    return (
        <ImageBackground
         style={styles.background} 
         source={require("../assets/background.png") } >

            <Image 
                source={require("../assets/logo.png") } 
                style={styles.logostyle} />
            <View style={styles.connectbuttoncontainer}>
                <Text style={styles.buttontext}>{connectText}</Text>
            </View>
            <View style={styles.monitorbuttoncontainer}>
                <Text style={styles.buttontext}>{monitorText}</Text>
            </View>
         </ImageBackground>
    );
}

const styles = StyleSheet.create({
    background: {
        flex: 1,
        justifyContent: "flex-end",
        alignItems: "center"
    },
    buttontext: {
        fontSize: 24,
        //fontFamily: "Cochin",
        color: "white"
    },
    connectbuttoncontainer: {
        width: "100%",
        height: 70,
        backgroundColor: "#fc5c65",
        alignItems: "center",
        justifyContent: "center"
    },
    logostyle: {
        width:250,
        height:250,
        position:"absolute",
        top:70
    },
    monitorbuttoncontainer: {
        width: "100%",
        height: 70,
        backgroundColor: "#4ecdc4",
        alignItems: "center",
        justifyContent: "center"
    }
    })

export default WelcomeScreen;