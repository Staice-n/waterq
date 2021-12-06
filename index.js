var firebaseConfig = 
{
    apiKey: "AIzaSyDiIvwiA5-AWvk1V-AWiEKJuIMOZFAHnAE",
    authDomain: "water-quality-a111a.firebaseapp.com",
    projectId: "water-quality-a111a",
    storageBucket: "water-quality-a111a.appspot.com",
    messagingSenderId: "541149674148",
    appId: "1:541149674148:web:50ba225020f42216400431",
    measurementId: "G-JGF22YK8E2"
  };
  //initialize firebase
firebase.initializeApp(firebaseConfig); 

const auth = firebase.auth()
const database = firebase.database()
 //setup register function
function register_btn ()
{
	full_name = document.getElementById('full_name').value;
	email= document.getElementById('email').value;
	passwordd = document.getElementById('passwordd').value;
	
	auth.createUserWithEmailAndPassword(email, passwordd)
	.then(function(){
		var user = auth.currentUser
		var database_ref = database.ref()
		var user_data = 
		{
			full_name : full_name,
			email : email,
			passwordd : passwordd,
			last_login : Date.now()
			
			
		}
		database_ref.child('users/' + user.uid).set(user_data)
		alert('User Created!!')
	})
    .catch(function(error){
		var errorCode = error.code;
		var errorMessage = error.message;
		alert(error_message)
	})		
} 




