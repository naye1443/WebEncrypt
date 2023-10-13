'use client'

/*TODO

- Add option for use to add key or to have a random 64-bit key generated for them.
    - This key generation should be processed on server and returned back to user.
    - Precursor: - Add Key 64-bit key generation to server side

- Create python modules for different block cipher modes.
    - These modules will be implmented in seperate python files. One file containing different Block cipher modes.
    (Note) Other modules will be created to implement other symmetric/asymmetric encryption methods with their respective modes.

- Use modules to handle different client request for encryption/Decryption.

*/

import React, {createContext , useState, useEffect} from 'react';
import axios from 'axios';
import Button from '@mui/material/Button';
import TextField from '@mui/material/TextField';
import FormControl from '@mui/material/FormControl';
import FormControlLabel from '@mui/material/FormControlLabel';
import FormGroup from '@mui/material/FormGroup';
import { FormLabel, RadioGroup, Container} from '@mui/material';
import Radio from '@mui/material/Radio';
import { spacing } from '@mui/system';


function Des(props){

    const {value, index}= props

    const [mode, setMode] = useState('Encrypt');
    const [radio, setRadio] = useState('ofb');
    const [Text, setText] = useState('');

    // Toggles Encryption/Decryption
    const toggleMode = () => {
        mode == 'Encrypt' ? setMode('Decrypt') : setMode('Encrypt');
    }

    const Submit = (e) => {
        e.preventDefault();

        console.log("We in this bit");

        const form = new FormData();
        form.append("Mode", mode.toString());
        form.append("Radio", radio.toString());
        form.append("Text", Text.toString());

        const config = {
            method: 'POST',
            url: 'http://127.0.0.1:5000/encrypt',
            data: form
        }
        axios(config).then((res) => console.log(res));
    }

    return(
        <>
            { value === index && (
            <FormControl onSubmit={Submit} >
                <Container sx={{mb: 2}}>
                    <FormLabel id="DES-BCM-control" >Encrypt/Decrypt</FormLabel>
                </Container>
                <Container sx={{mb: 2}}>
                    <Button variant="contained" onClick={toggleMode} onChange={(e) => setMode(e.target.value)}>{mode}</Button>
                </Container>
                    <FormLabel id="demo-radio-buttons-group-label">Block Cipher Mode</FormLabel>
                    <RadioGroup 
                        defaultValue="ofb"
                        onChange={(e) => setRadio(e.target.value)}
                        row={true}
                    >
                        <FormControlLabel value="ofb" control={<Radio />} label="Output Feedback" />
                        <FormControlLabel value="cm" control={<Radio/>} label="Counter" />
                        <FormControlLabel value="cfm" control={<Radio/>} label="Cipher Feedback" />
                    </RadioGroup>
            </FormControl>
            )}
        </>
    )
}

export default Des