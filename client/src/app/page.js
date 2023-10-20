"use client"

import {useState, useEffect} from 'react'
import styles from './page.module.css';
import {Container, Stack, TextField, Button, Tab, Tabs} from '@mui/material'
import DES from './components/Des';
import Elgamal from './components/Elgamal';
import {Context} from './components/Context';
import axios from 'axios';

export default function Home() {

  const [scheme, setScheme] = useState('DES');  // used to change tab and select scheme
  const [EncryptOrDcrypt, setEncryptOrDcrypt] = useState ('Encrypt')
  const [key, setKey] = useState ('');
  const [CipherMode, setCipherMode] = useState('OFB');
  const [Text, setText] = useState('');

  // Determines active tab
  const [SchemeTab, setSchemeTab] = useState(0);

  // Handle changing tab
  const handleChange = (event, newvalue) => { setSchemeTab(newvalue)};

  // Used to send context to Des Tab
  const DesForm = {
    EncryptOrDcrypt, setEncryptOrDcrypt,
    scheme, setScheme,
    key, setKey,
    CipherMode, setCipherMode,
  }

  useEffect(()=>{
    console.log("effect called");
  }, [scheme])

  const Submit = (e) => {
    e.preventDefault();

    const form = new FormData();
    form.append("EncryptOrDcrypt", EncryptOrDcrypt.toString());
    form.append("CipherMode", CipherMode.toString());
    form.append("key", key.toString());
    form.append("Scheme", scheme.toString());

    const config = {
        method: 'POST',
        url: 'http://127.0.0.1:5000/encrypt',
        data: form
    }
    axios(config).then((res) => console.log(res));
  }
  
  return (
    <main className={styles.main}>
      <Context.Provider value={DesForm}>
        <div><h1>EncryptWeb</h1></div>
        <Container >
          <box sx={{ borderBottom: 1, borderColor: 'divider' }}>
            <Tabs value={SchemeTab} onChange={handleChange}>
              <Tab label="DES"></Tab>
              <Tab label="Elgamal"></Tab>
            </Tabs>
          </box>
          <Container maxWidth="lg" sx={{ display:'flex',alignContent: "center", justifyContent: "center"}}>
            <DES value={SchemeTab} index={0}></DES>
            <Elgamal value={SchemeTab} index={1}></Elgamal>
          </Container>
            <Container>
              <Stack spacing={2}>
                <TextField
                    id="filled-basic"
                    label="plaintext"
                    variant="filled"
                    multiline
                    minRows={4}
                    helperText="Plaintext here"
                    onChange={(e) => setText(e.target.value)}
                />
                  <TextField
                    id="filled-basic"
                    label="plaintext"
                    variant="filled"
                    multiline
                    minRows={4}
                    helperText="Plaintext here"
                    onChange={(e) => setText(e.target.value)}
                />
                <Container>
                  <Button variant="contained" type='submit' onClick={Submit}>Encrypt</Button>
                </Container>
              </Stack>
            </Container>
        </Container>
      </Context.Provider>
    </main>
  )
}
