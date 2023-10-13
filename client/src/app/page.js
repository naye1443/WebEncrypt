"use client"

import {useState, useEffect, useContext } from 'react'
import Image from 'next/image';
import styles from './page.module.css';
import DES from './components/Des';
import {Container, Stack, TextField, Button, Tab, Tabs} from '@mui/material'
import Elgamal from './components/Elgamal';

export default function Home() {

  const [scheme, setScheme] = useState('DES');
  const [value, setValue] = useState(0);
  const [Text, setText] = useState('');

  useEffect(()=>{
    console.log("effect called");
  }, [scheme])

  const renderScheme = ()=>{
    return (
    scheme == "DES" ? <DES></DES>: <Elgamal></Elgamal>);
    
  }

  // Handle changing tab
  const handleChange = (event, newvalue) => { setValue(newvalue)};
  
  return (
    <main className={styles.main}>
      <div>Test div</div>
      <Container >
        <box sx={{ borderBottom: 1, borderColor: 'divider' }}>
          <Tabs value={value} onChange={handleChange}>
            <Tab label="DES"></Tab>
            <Tab label="Elgamal"></Tab>
          </Tabs>
        </box>
        <Container maxWidth="lg">
          <DES value={value} index={0}></DES>
          <Elgamal value={value} index={1}></Elgamal>
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
                <Button variant="contained" type='submit' >Encrypt</Button>
              </Container>
            </Stack>
          </Container>
      </Container>
    </main>
  )
}
