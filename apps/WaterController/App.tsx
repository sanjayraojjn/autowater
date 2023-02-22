import { StatusBar } from 'expo-status-bar';
import { StyleSheet, Text, View } from 'react-native';

//import WelcomeScreen from './app/screens/WelcomeScreen';
import SerchingDevices from './app/src/SearchingDevices';

const App = () => {

  return (
   /*<View style={styles.centeritem}>
    <Text > The pizza text '🍕'</Text>
   </View>*/
   
  <SerchingDevices />
  );
}

const styles = StyleSheet.create({
  centeritem: {
      justifyContent: "center",
      alignItems: "center",
      flex:1
  },
});

export default App;