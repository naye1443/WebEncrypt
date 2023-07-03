'use client'

import React, {createContext , useState, useEffect} from 'react';
import axios from 'axios';
import Button from '@mui/material/Button';
import TextField from '@mui/material/TextField';
import FormControl from '@mui/material/FormControl';
import FormControlLabel from '@mui/material/FormControlLabel';
import { FormLabel, RadioGroup, Radio } from '@mui/material';

function Des(){

    const [mode, setMode] = useState('Encrypt');
    const [Radio, setRadio] = useState('ofb');
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
        form.append("Radio", Radio.toString());
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
            <div>Inside Div</div>
            <container >
                <form onSubmit={Submit}>
                    <box sx={{display: 'flex'}} onChange={(e) => setMode(e.target.value)}>
                        <Button variant="contained" onClick={toggleMode}>{mode}</Button>
                    </box>
                    <box>
                        <FormControl>
                            <FormLabel id="demo-radio-buttons-group-label">Block Cipher Mode</FormLabel>
                            <RadioGroup
                            defaultValue="ofb"
                            onChange={(e) => setRadio(e.target.value)}>
                                <FormControlLabel value="ofb" control={<Radio/>} label="Output Feedback mode" />
                                <FormControlLabel value="cm" control={<Radio/>} label="Counter mode" />
                                <FormControlLabel value="cfm" control={<Radio/>} label="Cipher Feedback mode" />
                            </RadioGroup>
                        </FormControl>
                    </box>
                    <box sx={{display: 'flex'}} onChange={(e) => setText(e.target.value)}>
                        <TextField
                            id="filled-basic"
                            label="plaintext"
                            variant="filled"
                            multiline
                            minRows={4}
                            helperText="Plaintext here"
                        />
                    </box>
                    <box sx={{display: 'flex'}}>
                        <Button variant="contained" type='submit' >{mode}</Button>
                    </box>
                </form>
            </container>
        </>
    )
}

export default Des