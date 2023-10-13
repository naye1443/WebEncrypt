import React, {useState, useContext, useEffect} from "react";
import {Button, Container, FormControl, FormLabel, TextField } from "@mui/material";
import axios from "axios";

function Elgamal(props){

    const {value, index}= props

    const [mode, setMode] = useState('Encrypt');
    const [radio, setRadio] = useState('');
    const [Text, setText] = useState('');

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

    // Toggles Encryption/Decryption
    const toggleMode = () => {
        mode == 'Encrypt' ? setMode('Decrypt') : setMode('Encrypt');
    }

    return(
        <> { value === index && (
            <FormControl onSubmit={Submit} >
                <Container sx={{mb: 2}}>
                    <FormLabel id="Elgamal-BCM-control" sx={{ display: "flex", justifyContent: "center"}}>Encrypt/Decrypt</FormLabel>
                </Container>
                <Container sx={{mb: 2}}>
                    <TextField label="Generator" InputProps={{readOnly: true,}} sx={{ m: 2}}/>
                    <TextField label="modulo Prime" InputProps={{readOnly: true,}} sx={{ m: 2}}/>
                    <TextField label="computed public key" InputProps={{readOnly: true,}} sx={{ m: 2}}/>
                    <TextField label="private Key" InputProps={{readOnly: true,}} helperText="DO NOT SHARE" sx={{ m: 2}}/>
                </Container>
                <Container sx={{mb: 2}}>
                    <Button variant="contained" onClick={toggleMode} onChange={(e) => setMode(e.target.value)}>{mode}</Button>
                </Container>
            </FormControl>
            )}
        </>
    )

}



export default Elgamal