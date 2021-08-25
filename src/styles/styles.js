import styled from 'styled-components'
import { View, Text, Image } from 'react-native';
import { Constants } from 'expo-constants';

const StatusBarHeight = Constants.StatusBarHeight;

// Colors
export const Colors = {
/* Add HEX colour (#ffffff) and call via 
    */
    primary: "",
    secondary: "",

};

// Add any new colors to this structure
const { primary, secondary } = Colors;

export const StyledContainer = styled.View`
    flex: 1;
    padding: 25px;
    background-color: ${primary};
    padding-top: ${StatusBarHeight + 10}px
`

export const InnerContainer = styled.View`
    flex: 1;
    width: 100%;
    align-items: center;
`

export const PageLogo = styled.Image`
    width: 50px;
    height: 50px;
`

export const PageTitle = styled.Text`
    font-size: 30px;
    text-align: center;
`