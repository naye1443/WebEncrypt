'use client'

import {React, useContext} from 'react';
import Button from '@mui/material/Button';
import TextField from '@mui/material/TextField';
import FormControl from '@mui/material/FormControl';
import FormControlLabel from '@mui/material/FormControlLabel';
import { FormLabel, RadioGroup, Container, Stack, Tooltip} from '@mui/material';
import Radio from '@mui/material/Radio';
import {Context} from './Context';

function Des(props){

    const {value ,index} = props

    const {
        EncryptOrDcrypt, setEncryptOrDcrypt,
        scheme, setScheme,
        key, setKey,
        CipherMode, setCipherMode,
    } = useContext(Context)

    // Toggles Encryption/Decryption
    const toggleEncryptOrDcrypt = () => {
        EncryptOrDcrypt == 'Encrypt' ? setEncryptOrDcrypt('Decrypt') : setEncryptOrDcrypt('Encrypt');
    }

    return(
        <>
            { value === index && (
            <FormControl>
                <Container sx={{mb: 2}}>
                    <FormLabel id="DES-BCM-control" >Encrypt/Decrypt</FormLabel>
                </Container>
                <Stack
                  direction="row"
                  justifyContent="center"
                  alignItems="center"
                  spacing={1}>
                    <Container >
                        <Button variant="contained" onClick={toggleEncryptOrDcrypt}>{scheme}</Button>
                    </Container>
                    <Container >
                        <Tooltip title=
                        {<p> If left empty, a randomly generated key will be applied</p>}
                        placement="top-start"
                        >
                            <TextField
                            id="filled-basic"
                            label="plaintext"
                            variant="filled"
                            multiline
                            minRows={1}
                            helperText="Enter key here"
                            value={key} // Used to persist key when changing tabs
                            onChange={event => setKey(event.target.value)}    
                            />
                        </Tooltip>
                    </Container>
                </Stack>
                <Container sx={{mb: 2}}>
                    <FormLabel id="demo-radio-buttons-group-label">Block Cipher Mode</FormLabel>
                    <RadioGroup 
                        defaultValue="ofb"
                        onChange={event => setCipherMode(event.target.value)}
                        row={true}
                    >
                        <FormControlLabel value="ofb" control={<Radio />} label="Output Feedback" />
                        <FormControlLabel value="cm" control={<Radio/>} label="Counter" />
                        <FormControlLabel value="cfm" control={<Radio/>} label="Cipher Feedback" />
                    </RadioGroup>
                </Container>
            </FormControl>
            )}
        </>
    )
}

export default Des