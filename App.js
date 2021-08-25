/*
 ###################################################
 # Remove this before commiting to your own branch #
 ###################################################
 */

// Imports
import React from 'react';

// Expo/react 
import { StatusBar } from 'expo-status-bar';
import { StyleSheet, Text, View } from 'react-native';

// Screens
import HomeScreen from './src/screens/HomeScreen';
import LogInScreen from './src/screens/LogInScreen';

// Navigation 
import { createNativeStackNavigator } from '@react-navigation/native-stack';
import { NavigationContainer } from '@react-navigation/native';

// Screen stack navigator
const ScreenStack = createNativeStackNavigator();


export default function App() {
  return (
    <NavigationContainer>
      <ScreenStack.Navigator>
        <ScreenStack.Screen
          name='Home Page'
          component={HomeScreen}
        />
        <ScreenStack.Screen 
          name="LogInScreen"
          component={LogInScreen}
        />
      </ScreenStack.Navigator>
    </NavigationContainer>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#fff',
    alignItems: 'center',
    justifyContent: 'center',
  },
});
