import Image from 'next/image';
import styles from './page.module.css';
import Des from './components/Des.js';

export default function Home() {
  return (
    <main className={styles.main}>
      <div>Test div</div>
      <Des></Des>
    </main>
  )
}
